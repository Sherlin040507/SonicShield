/*
  SonicShield node: prototype firmware (ESP32, Arduino framework)

  Status: UNTESTED on hardware. Written as a starting point.

  What it does:
    - Reads solar panel voltage through a voltage divider on an ADC pin
    - Keeps a slow-moving baseline of recent readings
    - If voltage falls below THRESHOLD_RATIO * baseline, triggers a
      cleaning pulse on SAW_DRIVE_PIN
    - Logs CSV over serial: time_ms,voltage_V,baseline_V,cleaning

  Wiring:
    Panel+ --[R1]--+--[R2]-- GND      (ADC reads the middle point)
                   |
                GPIO34 (ADC1)
    GPIO25 -> SAW driver stage input

  Set R1/R2 so the ADC pin never exceeds 3.3 V at maximum panel voltage.
*/

const int   ADC_PIN         = 34;
const int   SAW_DRIVE_PIN   = 25;

const float ADC_REF_V       = 3.3;
const float ADC_MAX         = 4095.0;
const float R1_OHMS         = 100000.0;  // change to match your divider
const float R2_OHMS         = 33000.0;   // change to match your divider

const float THRESHOLD_RATIO = 0.85;      // trigger below 85% of baseline
const float BASELINE_ALPHA  = 0.01;      // smoothing factor for baseline

const unsigned long SAMPLE_INTERVAL_MS   = 2000;
const unsigned long CLEAN_DURATION_MS    = 3000;
const unsigned long CLEAN_COOLDOWN_MS    = 600000;  // 10 min between cleans

float baseline = 0.0;
bool  baselineReady = false;
unsigned long lastSample = 0;
unsigned long lastClean  = 0;

float readPanelVoltage() {
  const int samples = 16;
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(ADC_PIN);
    delay(2);
  }
  float adcAvg = sum / (float)samples;
  float vAdc = (adcAvg / ADC_MAX) * ADC_REF_V;
  return vAdc * (R1_OHMS + R2_OHMS) / R2_OHMS;
}

void cleaningPulse() {
  digitalWrite(SAW_DRIVE_PIN, HIGH);
  delay(CLEAN_DURATION_MS);
  digitalWrite(SAW_DRIVE_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(SAW_DRIVE_PIN, OUTPUT);
  digitalWrite(SAW_DRIVE_PIN, LOW);
  analogReadResolution(12);
  Serial.println("time_ms,voltage_V,baseline_V,cleaning");
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample < SAMPLE_INTERVAL_MS) return;
  lastSample = now;

  float v = readPanelVoltage();

  if (!baselineReady) {
    baseline = v;
    baselineReady = true;
  } else {
    baseline = (1.0 - BASELINE_ALPHA) * baseline + BASELINE_ALPHA * v;
  }

  int cleaning = 0;
  bool cooledDown = (lastClean == 0) || (now - lastClean > CLEAN_COOLDOWN_MS);
  if (v < THRESHOLD_RATIO * baseline && cooledDown) {
    cleaning = 1;
    Serial.printf("%lu,%.3f,%.3f,%d\n", now, v, baseline, cleaning);
    cleaningPulse();
    lastClean = millis();
    return;
  }

  Serial.printf("%lu,%.3f,%.3f,%d\n", now, v, baseline, cleaning);
}
