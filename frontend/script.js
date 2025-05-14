// Station coordinates (Dehradun stations)
const stationCoords = {
  'ISBT': [30.3184, 78.0324],
  'ClockTower': [30.3252, 78.0413],
  'Balliwala': [30.3344, 78.0298],
  'PratapNagar': [30.3267, 78.0488],
  'Raipur': [30.3164, 78.0608],
  'Malsi': [30.3674, 78.0833]
};

let map;
let routeLayer;

// Initialize map
function initMap() {
  map = L.map('map').setView([30.3252, 78.0413], 13);
  L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '© OpenStreetMap contributors'
  }).addTo(map);

  // Add station markers
  for (let station in stationCoords) {
    L.marker(stationCoords[station])
      .bindPopup(station)
      .addTo(map);
  }
}

// Load route data and display on map
function loadBackendRoute() {
  fetch('output.json')
    .then(response => response.json())
    .then(data => {
      const sourceInput = document.getElementById("source");
      const destinationInput = document.getElementById("destination");
      const routeDetails = document.getElementById("routeDetails");

      sourceInput.value = data.source_name;
      destinationInput.value = data.destination_name;

      // Display route summary
      routeDetails.innerHTML = `
        <h2>🚏 Route Summary</h2>
        <p><strong>From:</strong> ${data.source_name}</p>
        <p><strong>To:</strong> ${data.destination_name}</p>
        <p><strong>Distance:</strong> ${data.distance} minutes</p>
        <p><strong>Path:</strong> ${data.path_names.join(" → ")}</p>
      `;

      // Draw route on map
      drawRoute(data.path_names);
    })
    .catch(error => {
      console.error("Failed to load route data:", error);
      alert("Could not load route data.");
    });
}

// Draw route on map
function drawRoute(pathNames) {
  if (routeLayer) {
    map.removeLayer(routeLayer);
  }

  const routeCoords = pathNames.map(station => stationCoords[station]);
  routeLayer = L.polyline(routeCoords, {
    color: '#00ffe7',
    weight: 4,
    opacity: 0.8
  }).addTo(map);

  // Fit map to show entire route
  map.fitBounds(routeLayer.getBounds(), { padding: [50, 50] });
}

function swapStations() {
  const source = document.getElementById("source");
  const destination = document.getElementById("destination");
  [source.value, destination.value] = [destination.value, source.value];
}

function clearRoute() {
  document.getElementById("source").value = "";
  document.getElementById("destination").value = "";
  document.getElementById("routeDetails").innerHTML = "";
  if (routeLayer) {
    map.removeLayer(routeLayer);
  }
}

function showNearby() {
  if ("geolocation" in navigator) {
    navigator.geolocation.getCurrentPosition(position => {
      const userLat = position.coords.latitude;
      const userLng = position.coords.longitude;
      map.setView([userLat, userLng], 14);
    });
  } else {
    alert("Location services not available");
  }
}

// Initialize map when page loads
window.onload = () => {
  initMap();
  loadBackendRoute();
};