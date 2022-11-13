This section does not have source code.

1. Sleeping process (S) -> during a sleep()
2. Zombie process (Z) -> child process exits before parent (so still the entry is there in process table)
3. Orphan process -> child process still running even though parent exited (reparenting done by OS)

run example in 15.waitpid_system_call_example folder and perhaps modify it or just observe using
ps aux | grep Z  (or S for sleeping)