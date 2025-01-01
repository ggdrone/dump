#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function for reading fan speed from file.
// Don't have CPU-fan sensor on this machine
/*int readFanSpeed()
{
  const char *fanspeedfile = "WHERE IS THE FILE?";
  FILE *fp                 = fopen(fanspeedfile, "r");

  if (fp == NULL)
  {
    printf("Error: could not open file %s", fanspeedfile);
    return 1;
  }

  // Reading the temperature value from WHERE IS THE FILE?
  char buffer[256];
  if (fgets(buffer, sizeof(buffer), fp))
  {
    printf("The fan is currently spinning at: %.2f RPM", );
  }
  else
  {
    printf("Error: could not read from file %s\n", fanspeedfile);
    fclose(fp);
    return 1;
  } 

  // Close the file.
  fclose(fp);
  return 0; 
 } */

// Function for reading CPU temperatur from file.
int readTemp()
{
  const char *tempfile = "/sys/class/hwmon/hwmon1/temp1_input";
  FILE *fp             = fopen(tempfile, "r");

  if (fp == NULL)
  {
    printf("Error: could not open file %s", tempfile);
    return 1;
  }

  // Reading the temperature value from temp1_input
  char buffer[256];
  if (fgets(buffer, sizeof(buffer), fp))
  {
    // Converting from millidegrees to Celcius.
    int temp_millidegrees  = atoi(buffer); // atoi() string -> int
    float temp_celsius     = temp_millidegrees / 1000.0;
    printf("CPU temperature is currently: %.2f *C\n", temp_celsius);
  }
  else
  {
    printf("Error: could not read from file %s\n", tempfile);
    fclose(fp);
    return 1;
  } 

  // Close the file.
  fclose(fp);
  return 0;
}

int main(void)
{
  while (1)
  {
    int cpu_temp = readTemp();
    sleep(5);
  }
  return 0;
}
