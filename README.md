File Watcher - C++
-

A file watcher implemented using the std::filesystem library


Features:
-

- Detects when and which file was added/removed/modified given a specific path


Planned Features:
-

- Detect which file specifically got modified
- Parse changed file by .ext type
- Have an event be fired off which can be listened for by any other code interested in specific .ext file types
- (Maybe) Write Output Log to a File, since its currently bugged due to ASNI coding in Clion output console  


<span style="color: #d42c7d"> Note: </span>
-
For anyone building/cloning this project, on Clion the output will not be displayed properly on the output console (Will fix at some point)

<span style="color: #d42c7d"> Options: </span> Use your cmd terminal to execute the .exe to see console logs or remove the Logger class and use regular prints (std::cout or printf) or replace all instances of '\n' with std::endl (will have performance costs)
