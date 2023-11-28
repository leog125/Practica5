document.addEventListener("DOMContentLoaded", function () {
  // Function to get the last sensor value from the server
  function getLastSensorValue() {
    fetch("http://130.130.2.68:5000/api/getSensorValue_All")
      .then((response) => response.json())
      .then((data) => {
        if (data.success) {
          // Update the sensor value on the page
          const actualValueSpan1 = document.getElementById("actualValue");
          actualValueSpan1.textContent = data.value.Value1;
          const actualValueSpan2 = document.getElementById("actualValue2");
          actualValueSpan2.textContent = data.value.Value2;
          const actualValueSpan3 = document.getElementById("actualValue3");
          actualValueSpan3.textContent = data.value.Value3;
          const actualValueSpan4 = document.getElementById("actualValue4");
          actualValueSpan4.textContent = data.value.Value4;
          //Giroscopio
          const actualValueSpan5 = document.getElementById("actualValueX");
          actualValueSpan5.textContent = data.value.ValueX;
          const actualValueSpan6 = document.getElementById("actualValueY");
          actualValueSpan6.textContent = data.value.ValueY;
          const actualValueSpan7 = document.getElementById("actualValueZ");
          actualValueSpan7.textContent = data.value.ValueZ;
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