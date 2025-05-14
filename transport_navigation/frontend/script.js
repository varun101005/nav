// Load backend route data from output.json
function loadBackendRoute() {
  fetch('output.json')
    .then(response => response.json())
    .then(data => {
      const sourceInput = document.getElementById("source");
      const destinationInput = document.getElementById("destination");
      const routeDetails = document.getElementById("routeDetails");

      // Set input fields
      sourceInput.value = data.source;
      destinationInput.value = data.destination;

      // Display route summary
      routeDetails.innerHTML = `
        <h2>🚏 Route Summary</h2>
        <p><strong>From:</strong> Station ${data.source}</p>
        <p><strong>To:</strong> Station ${data.destination}</p>
        <p><strong>Distance:</strong> ${data.distance} units</p>
        <p><strong>Path:</strong> ${data.path.join(" → ")}</p>
      `;
    })
    .catch(error => {
      console.error("❌ Failed to load output.json:", error);
      alert("Could not load route data.");
    });
}

// Swap source and destination
function swapStations() {
  const source = document.getElementById("source");
  const destination = document.getElementById("destination");
  [source.value, destination.value] = [destination.value, source.value];
}

// Clear all inputs and route details
function clearRoute() {
  document.getElementById("source").value = "";
  document.getElementById("destination").value = "";
  document.getElementById("routeDetails").innerHTML = "";
}

// Placeholder for future GPS integration
function showNearby() {
  alert("📍 This feature will show nearby stations using location API in future updates.");
}

// OPTIONAL: Auto-load route on page load
// window.onload = loadBackendRoute;
