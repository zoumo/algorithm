
# README

this program a sample of reservoir sampling algorithm. 
it sample m line from n line input.

###Usage

reservoir_sampling -m num [-l] [-is input | -os output]

###Example

    [1] cat input | ./reservoir_sampling -m=1000 > output
    [2] ./reservoir_sampling -m=1000 -is=./input -os=./output
    [3] cat input | ./reservoir_sampling -m=1000 -l

###Options
    -is (input stream, default is stdin) type: string default: "null"
    -l (if -l is set up, than line number will be print) type: bool default: false
    -m (the size of output) type: int32 default: 0
    -os (output stream, default is stdout) type: string default: "null"