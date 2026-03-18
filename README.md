# ShardKV  
Modern C++ 23 Sharded KV Store for 64-bit systems.


### Dependancies
OS: ```Linux (WSL)```  
Ready: ```sudo apt update```  
Compiler: ```sudo apt install clang```  
Build Tool: ```sudo apt install cmake```  
Enable Build Script: ```chmod +x rebuild_run.sh && chmod +x rebuild_test```
Abseil Hash Libs: ```cd src && git clone https://github.com/abseil/abseil-cpp.git```

#### Rebuild & Run
```./rebuild_run.sh```

#### Shortcut (Zed, Cursor, VSCode)
1. Locate your IDE keybind settings, then in your keymap.json add:
```
    {
        "context": "Workspace",
        "bindings": {
            "ctrl-'": ["task::Spawn", { "task_name": "rebuild_run" }],
            "ctrl-t": ["task::Spawn", { "task_name": "test" }]
            "ctrl-b": ["task::Spawn", { "task_name": "rebuild" }]
        }
    },
```
2. Notice this project has a .zed folder with a tasks.json. If you are using zed this will work fine,  
if you use cursor or vscode, create a tasks.json in a .cursor or .vscode directory respectively.  
3. Select the terminal then hit your keybind (ctrl-') to rebuild and run. Test using (ctrl-t).
