// Load stations into dropdowns
async function loadStations() {
  try {
    const response = await fetch('../data/stations.csv');
    const data = await response.text();
    const stations = data.split('\n')
      .filter(line => line.trim())
      .map(line => {
        const [id, name] = line.split(',');
        return { id: parseInt(id), name: name.trim() };
      });

    const sourceSelect = document.getElementById('source');
    const destSelect = document.getElementById('destination');

    stations.forEach(station => {
      if (station.name) {
        const option = new Option(station.name, station.id);
        sourceSelect.add(option.cloneNode(true));
        destSelect.add(option);
      }
    });
  } catch (error) {
    console.error('Error loading stations:', error);
  }
}

// Find route between selected stations
async function findRoute() {
  const source = document.getElementById('source').value;
  const destination = document.getElementById('destination').value;

  if (!source || !destination) {
    alert('Please select both source and destination stations');
    return;
  }

  try {
    // Execute the C++ program with selected stations
    const response = await fetch(`/find-route?source=${source}&destination=${destination}`);
    const data = await response.json();
    
    displayRoute(data);
  } catch (error) {
    console.error('Error finding route:', error);
    alert('Error finding route. Please try again.');
  }
}

// Display route details
function displayRoute(data) {
  const routeDetails = document.getElementById('routeDetails');
  routeDetails.innerHTML = `
    <h2>🚏 Route Summary</h2>
    <p><strong>From:</strong> ${data.source_name}</p>
    <p><strong>To:</strong> ${data.destination_name}</p>
    <p><strong>Total Time:</strong> ${data.distance} minutes</p>
    <p><strong>Route:</strong> ${data.path_names.join(' → ')}</p>
  `;
}

// Swap source and destination
function swapStations() {
  const source = document.getElementById('source');
  const destination = document.getElementById('destination');
  [source.value, destination.value] = [destination.value, source.value];
}

// Clear all inputs and route details
function clearRoute() {
  document.getElementById('source').value = '';
  document.getElementById('destination').value = '';
  document.getElementById('routeDetails').innerHTML = '';
}

// Load stations when page loads
window.onload = loadStations;