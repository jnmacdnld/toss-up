#define MEASURE_BUTTON vexRT[Btn8R]

task Measure()
{
	// Define variables to store the state of the measure button
  bool current_state = MEASURE_BUTTON;
  bool last_state = false;

  // Define variables for the measuring itself
  long initial_encoder = 0;
  bool measuring = false;

  while (true)
  {
    // Store the current state
    current_state = vexRT[Btn8R];  

    // Determine whether the measure button was just released
    bool measure_released = current_state == false && last_state == true;

    // Handle the measure button being released
    if (measure_released)
    {
    	// If already measuring, stop measuring and display the mesasurment
    	if (measuring)
    	{
    		// Stop measuring
    		measuring = false;

    		// Calculate the distance moved
    		int distance = nMotorEncoder[backLeftDrive] - initial_encoder;

    		// Print the distance
    		writeDebugStreamLine("Moved %i ticks\n", distance);
			}
			// If not yet measuring, start measuring
			else
			{
				// Start measuring
				measuring = true;

				// Store the initial position of the encoder for later
    		initial_encoder = nMotorEncoder[backLeftDrive];

    		// Print a message that measuring has started
    		writeDebugStreamLine("\nStarted mesasurment");
			}
    }


    // Update last_state for the next iteration
    last_state = current_state;

    // Don't hog CPU
    wait1Msec(25);
  }
}
