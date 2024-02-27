For correct work use the GDB instead of CLang

To correct work you should setup gdb with 'set print elements 0' and 'set print repeats 0'

If you use the VSCode you can add approriate commands in the launch.json in section "setupCommands"


    {    
        "text": "-interpreter-exec console \"set print elements 0\"",
        "ignoreFailures": true
    },
    {
        "text": "-interpreter-exec console \"set print repeats 0\"",
        "ignoreFailures": true
    }
