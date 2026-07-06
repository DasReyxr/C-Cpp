#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>


// ─── HTML PAGE ────────────────────────────────────────────────────────────────
// Served inline so no SD card / SPIFFS is needed.
const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>ESP8266 LED Control</title>
  <style>
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

    :root {
      --bg:        #0d0d0f;
      --surface:   #16171c;
      --border:    #2a2b33;
      --accent:    #f5c842;
      --on:        #f5c842;
      --off:       #3a3b45;
      --text:      #e8e9f0;
      --muted:     #6b6c7a;
      --radius:    14px;
      --font:      'Courier New', Courier, monospace;
    }

    body {
      background: var(--bg);
      color: var(--text);
      font-family: var(--font);
      min-height: 100vh;
      display: flex;
      align-items: center;
      justify-content: center;
      padding: 1.5rem;
    }

    .card {
      background: var(--surface);
      border: 1px solid var(--border);
      border-radius: var(--radius);
      padding: 2.5rem 2rem;
      width: 100%;
      max-width: 360px;
      text-align: center;
    }

    .eyebrow {
      font-size: 0.65rem;
      letter-spacing: 0.18em;
      text-transform: uppercase;
      color: var(--muted);
      margin-bottom: 0.4rem;
    }

    h1 {
      font-size: 1.4rem;
      font-weight: 700;
      letter-spacing: 0.04em;
      color: var(--text);
      margin-bottom: 2rem;
    }

    /* Bulb icon */
    .bulb-wrap {
      margin: 0 auto 2rem;
      width: 96px;
      height: 96px;
      border-radius: 50%;
      display: flex;
      align-items: center;
      justify-content: center;
      transition: background 0.35s, box-shadow 0.35s;
    }
    .bulb-wrap.is-on {
      background: rgba(245, 200, 66, 0.12);
      box-shadow: 0 0 40px rgba(245, 200, 66, 0.35);
    }
    .bulb-wrap.is-off {
      background: rgba(58, 59, 69, 0.25);
      box-shadow: none;
    }
    .bulb-wrap svg { width: 52px; height: 52px; }

    /* Status badge */
    .status {
      display: inline-flex;
      align-items: center;
      gap: 0.45rem;
      font-size: 0.75rem;
      letter-spacing: 0.12em;
      text-transform: uppercase;
      margin-bottom: 2rem;
      padding: 0.35rem 0.9rem;
      border-radius: 999px;
      border: 1px solid var(--border);
      color: var(--muted);
    }
    .status.is-on  { color: var(--on);  border-color: rgba(245,200,66,0.4); }
    .status.is-off { color: var(--muted); }

    .dot {
      width: 7px; height: 7px;
      border-radius: 50%;
      background: currentColor;
    }
    .dot.is-on  { animation: pulse 1.4s ease-in-out infinite; }
    @keyframes pulse {
      0%, 100% { opacity: 1; }
      50%       { opacity: 0.3; }
    }

    /* Toggle button */
    .btn {
      width: 100%;
      padding: 0.85rem 1rem;
      border: none;
      border-radius: 9px;
      font-family: var(--font);
      font-size: 0.9rem;
      font-weight: 700;
      letter-spacing: 0.1em;
      text-transform: uppercase;
      cursor: pointer;
      transition: opacity 0.15s, transform 0.1s;
    }
    .btn:active { transform: scale(0.97); }
    .btn.turn-on  { background: var(--accent); color: #0d0d0f; }
    .btn.turn-off { background: var(--off);    color: var(--muted); border: 1px solid var(--border); }

    /* IP footer */
    .footer {
      margin-top: 1.8rem;
      font-size: 0.62rem;
      letter-spacing: 0.1em;
      color: var(--muted);
    }
  </style>
</head>
<body>
  <div class="card">
    <p class="eyebrow">ESP8266 &bull; GPIO%GPIO%</p>
    <h1>LED Control</h1>

    <div class="bulb-wrap %BULBCLASS%">
      <!-- Lightbulb SVG -->
      <svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg">
        <path d="M12 2C8.13 2 5 5.13 5 9c0 2.38 1.19 4.47 3 5.74V17c0 .55.45 1 1 1h6c.55 0 1-.45 1-1v-2.26C17.81 13.47 19 11.38 19 9c0-3.87-3.13-7-7-7z"
              fill="%FILL%" opacity="%OPACITY%"/>
        <path d="M9 21c0 .55.45 1 1 1h4c.55 0 1-.45 1-1v-1H9v1z" fill="%FILL%" opacity="%OPACITY%"/>
        <line x1="9" y1="17" x2="15" y2="17" stroke="%STROKE%" stroke-width="1.5" stroke-linecap="round"/>
      </svg>
    </div>

    <div class="status %STATUSCLASS%">
      <span class="dot %DOTCLASS%"></span>
      <span>%STATUSTEXT%</span>
    </div>

    <form action="/toggle" method="POST">
      <button type="submit" class="btn %BTNCLASS%">%BTNLABEL%</button>
    </form>

    <p class="footer">IP &nbsp;&bull;&nbsp; %IP%</p>
  </div>
</body>
</html>
)rawliteral";


#endif