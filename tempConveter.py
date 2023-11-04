def getinput():
    while True:  # This will start an infinite loop that will keep asking for input until it's correct
        user_input = input("Enter a temperature in Fahrenheit (e.g., 23F) or Celsius (e.g., 23C), and I will convert it: ")
        
        if not user_input:  # Checks if the input is empty
            print("Please enter the value:")
            continue  # This will skip the rest of the loop and go back to the beginning
        
        unit = user_input[-1].lower()  # Extracts the unit
        
        if unit not in ("f", "c"):  # Validates the unit
            print("The unit must be 'F' or 'C'. Please use the correct format.")
            continue  # This will skip the rest of the loop and go back to the beginning
        
        try:
            temp = float(user_input[:-1])  # Tries to convert the number part to float
            return temp, unit  # If the try block is successful, it returns the values
        except ValueError:  # If it fails, it will go to the except block
            print("We have extra characters! Please use the format 23F or 23C for input.")

def convert_temp(temp, unit):
    if unit == "c":
        ftemp = temp * 9/5 + 32 
        result = f"{temp}°C is {ftemp}°F."
    elif unit == "f":
        ctemp = (temp - 32) * 5/9 
        result = f"{temp}°F is {ctemp}°C."
    else:
        # Handle unexpected unit
        result = "Unexpected unit. Please use 'C' for Celsius or 'F' for Fahrenheit."

    print(result)
    return result  # Return the result in case it needs to be used later.


