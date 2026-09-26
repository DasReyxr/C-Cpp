#pragma once
#include <Arduino.h>

static const char INDEX_HTML[] PROGMEM = R"rawhtml(
<!DOCTYPE html>
<html lang="es">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP8266 → STM32F401 Programmer</title>
<style>
  * { box-sizing: border-box; margin: 0; padding: 0; }
  body { font-family: monospace; background: #0d1117; color: #c9d1d9;
         display: flex; justify-content: center; padding: 2rem; min-height: 100vh; }
  .card { background: #161b22; border: 1px solid #30363d;
          border-radius: 10px; padding: 2rem; max-width: 480px; width: 100%; }
  h1 { font-size: 1.1rem; color: #58a6ff; margin-bottom: 0.3rem; }
  .sub { font-size: 0.75rem; color: #8b949e; margin-bottom: 1.5rem; }
  .drop { border: 2px dashed #30363d; border-radius: 8px;
          padding: 2rem; text-align: center; cursor: pointer;
          transition: border-color .2s; margin-bottom: 1rem; }
  .drop:hover, .drop.over { border-color: #58a6ff; }
  .drop input { display: none; }
  .drop .icon { font-size: 2rem; margin-bottom: 0.5rem; }
  .drop p { font-size: 0.85rem; color: #8b949e; }
  #filename { font-size: 0.8rem; color: #3fb950; margin-top: 0.3rem; }
  button { width: 100%; padding: 0.7rem; background: #238636; color: #fff;
           border: none; border-radius: 6px; font-size: 0.9rem;
           cursor: pointer; font-family: monospace; transition: background .2s; }
  button:hover:not(:disabled) { background: #2ea043; }
  button:disabled { background: #21262d; color: #8b949e; cursor: default; }
  .progress-wrap { margin-top: 1rem; display: none; }
  .bar-bg { background: #21262d; border-radius: 4px; height: 8px; overflow: hidden; }
  .bar { background: #1f6feb; height: 100%; border-radius: 4px;
         width: 0%; transition: width .3s; }
  .log { margin-top: 1rem; background: #0d1117; border: 1px solid #30363d;
         border-radius: 6px; padding: 0.75rem; font-size: 0.75rem;
         color: #8b949e; min-height: 80px; max-height: 200px;
         overflow-y: auto; white-space: pre-wrap; }
  .ok  { color: #3fb950; }
  .err { color: #f85149; }
  .info { color: #58a6ff; }
</style>
</head>
<body>
<div class="card">
  <h1>⚡ ESP8266 SWD Programmer</h1>
  <div class="sub">NodeMCU v1 → STM32F401 BlackPill via SWD bit-bang</div>

  <div class="drop" id="dropzone">
    <div class="icon">📂</div>
    <p>Arrastra tu <strong>.bin</strong> aquí<br>o haz clic para seleccionar</p>
    <div id="filename"></div>
    <input type="file" id="fileInput" accept=".bin">
  </div>

  <button id="flashBtn" disabled onclick="startFlash()">Flash →</button>

  <div class="progress-wrap" id="progressWrap">
    <div style="display:flex;justify-content:space-between;font-size:0.75rem;margin-bottom:4px">
      <span id="progressLabel">0%</span>
      <span id="progressBytes">0 / 0 KB</span>
    </div>
    <div class="bar-bg"><div class="bar" id="bar"></div></div>
  </div>

  <div class="log" id="log">Esperando archivo .bin...\n</div>
</div>

<script>
let selectedFile = null;
let polling = null;

const dropzone  = document.getElementById('dropzone');
const fileInput = document.getElementById('fileInput');
const flashBtn  = document.getElementById('flashBtn');
const log       = document.getElementById('log');
const bar       = document.getElementById('bar');
const progWrap  = document.getElementById('progressWrap');
const progLabel = document.getElementById('progressLabel');
const progBytes = document.getElementById('progressBytes');

dropzone.addEventListener('click', () => fileInput.click());
dropzone.addEventListener('dragover', e => { e.preventDefault(); dropzone.classList.add('over'); });
dropzone.addEventListener('dragleave', () => dropzone.classList.remove('over'));
dropzone.addEventListener('drop', e => {
  e.preventDefault(); dropzone.classList.remove('over');
  handleFile(e.dataTransfer.files[0]);
});
fileInput.addEventListener('change', () => handleFile(fileInput.files[0]));

function handleFile(f) {
  if (!f || !f.name.endsWith('.bin')) { addLog('⚠ Solo se aceptan archivos .bin', 'err'); return; }
  selectedFile = f;
  document.getElementById('filename').textContent = `✓ ${f.name} (${(f.size/1024).toFixed(1)} KB)`;
  flashBtn.disabled = false;
  addLog(`Archivo: ${f.name} — ${f.size} bytes`, 'info');
}

function addLog(msg, cls) {
  const span = document.createElement('span');
  if (cls) span.className = cls;
  span.textContent = msg + '\n';
  log.appendChild(span);
  log.scrollTop = log.scrollHeight;
}

async function startFlash() {
  if (!selectedFile) return;
  flashBtn.disabled = true;
  progWrap.style.display = 'block';
  addLog('Subiendo archivo al ESP8266...', 'info');

  const fd = new FormData();
  fd.append('firmware', selectedFile);

  try {
    const resp = await fetch('/upload', { method: 'POST', body: fd });
    const txt  = await resp.text();
    if (!resp.ok) { addLog('Error al subir: ' + txt, 'err'); flashBtn.disabled = false; return; }
    addLog('Archivo subido. Programando...', 'info');
    polling = setInterval(pollStatus, 500);
  } catch (e) {
    addLog('Error de red: ' + e, 'err');
    flashBtn.disabled = false;
  }
}

async function pollStatus() {
  try {
    const resp = await fetch('/status');
    const data = await resp.json();

    const pct = data.total > 0 ? Math.round(data.progress * 100 / data.total) : 0;
    bar.style.width = pct + '%';
    progLabel.textContent = pct + '%';
    progBytes.textContent = `${(data.progress/1024).toFixed(1)} / ${(data.total/1024).toFixed(1)} KB`;

    if (data.message) addLog(data.message, data.state === 'ERROR' ? 'err' :
                                           data.state === 'DONE'  ? 'ok'  : '');

    if (data.state === 'DONE' || data.state === 'ERROR') {
      clearInterval(polling);
      flashBtn.disabled = false;
      bar.style.background = data.state === 'DONE' ? '#3fb950' : '#f85149';
    }
  } catch(e) {}
}
</script>
</body>
</html>
)rawhtml";