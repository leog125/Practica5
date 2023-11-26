document.addEventListener("DOMContentLoaded", function () {
  // Function to get the last sensor value from the server
  function getLastSensorValue() {
    fetch("http://192.168.10.2:5000/api/getSensorValue")
      .then((response) => response.json())
      .then((data) => {
        if (data.success) {
          // Update the sensor value on the page
          const actualValueSpan = document.getElementById("actualValue");
          actualValueSpan.textContent = data.last_value;
        } else {
          alert("Error: " + data.error);
        }
      })
      .catch((error) => alert("Error: " + error));
  }

  // Function to update sensor value on button click
  function updateSensorValueOnClick() {
    getLastSensorValue();
  }

  // Initial call to get the last sensor value
  getLastSensorValue();

  // Periodically update the sensor value (adjust the interval as needed)
  setInterval(getLastSensorValue, 10000); // Update every 10 seconds

  // Add click event listener to the button
  const updateButton = document.getElementById("Btn_Update");
  if (updateButton) {
    updateButton.addEventListener("click", updateSensorValueOnClick);
  } else {
    console.error('Button with ID "Btn_Update" not found in the document.');
  }

});

  // Function to update sensor value and change color to red
  function addSensor(sensorId) {
    // Change the color to red
    document.getElementById(sensorId).style.color = "red";
  }