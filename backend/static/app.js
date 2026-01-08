const citySelect = document.getElementById("city");
const srcSelect = document.getElementById("source");
const destSelect = document.getElementById("destination");
const output = document.getElementById("output");
const button = document.getElementById("findRoute");

function loadStations(city) {
  fetch(`/stations?city=${city}`)
    .then(res => res.json())
    .then(data => {
      srcSelect.innerHTML = "";
      destSelect.innerHTML = "";

      data.forEach(s => {
        srcSelect.add(new Option(s.name, s.id));
        destSelect.add(new Option(s.name, s.id));
      });
    });
}

citySelect.addEventListener("change", () => {
  loadStations(citySelect.value);
  output.textContent = "";
});

loadStations(citySelect.value);

button.addEventListener("click", async () => {
  const src = srcSelect.value;
  const dest = destSelect.value;

  if (src === dest) {
    output.textContent = "Source and destination cannot be same.";
    return;
  }

  output.textContent = "Calculating route...";

  try {
    const res = await fetch(`/route?src=${src}&dest=${dest}`);
    const data = await res.json();

    if (data.error) {
      output.textContent = data.error;
      return;
    }

    renderRoute(data);
  } catch {
    output.textContent = "Failed to connect to backend.";
  }
});

function renderRoute(data) {
  let html = `<strong>Total Time:</strong> ${data.total_time} minutes<br>`;
  html += `<strong>Estimated Fare:</strong> ₹${calculateFare(data.route)}<br><br>`;

  let currentLine = data.route[0].line;
  html += `<strong>${currentLine}</strong><ul>`;

  for (let i = 0; i < data.route.length; i++) {
    const step = data.route[i];

    if (step.line !== currentLine) {
      html += `</ul><div class="interchange">
               Change at <strong>${data.route[i-1].station}</strong>
               → ${step.line}
               </div><ul>`;
      currentLine = step.line;
    }

    html += `<li>${step.station}</li>`;
  }

  html += "</ul>";
  output.innerHTML = html;
}

function calculateFare(route) {
  let fare = 0;
  let prevLine = null;

  route.forEach((step, i) => {
    if (i === 0) {
      fare += step.line.includes("Metro") ? 10 : 5;
    } else if (step.line !== prevLine) {
      fare += 5;
    } else {
      fare += step.line.includes("Metro") ? 5 : 2;
    }
    prevLine = step.line;
  });

  return fare;
}
