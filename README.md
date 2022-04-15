# Car Park Automated System
A large car park requires an automated system which tracks vehicles as they enter and exit the
car park using their number plate and calculates the parking cost as they exit.
The input to your program will be from a file which will have (on each line) a time and date
and either a vehicle entering or exiting the car park.

Your program must use an appropriate data structure to track the vehicles currently in the car
park. When they leave they should be removed from this data structure and added to a history
data structure which stores all vehicles, entry and exit times and parking charge.

You will be provided with a small sample data file in the correct format to use when writing
and testing your program. However, the program should work with any file of this format (and
another file will be used when marking your work); therefore, your program should allow the user
to specify the input file name as a command line argument.

Parking prices will be calculated using the following table.

Duration              Price
less than 30 minutes  FREE
Up to 1 hour          £1.50
Up to 2 hours         £3.00
Up to 4 hours         £5.00
Up to 8 hours         £15.00
Over 8 hours          £30.00
