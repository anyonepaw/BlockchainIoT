# NS-3 project of integrating Blockchain (Tangle) in the Internet of Things

### CONFIGURE

Open terminal:


```
cd ...../BlockchainIoT/ns-3.29
```

Then type:
```
./waf configure

./waf build
```


//no need exactly

If you need more visibility into how Waf is building, try building with the -vvv flag:

```
./waf build -vvv.
```


### CONFIGURE BUGS

```
./ns3/make-event.h:665:20: error: unused typedef 'F' [-Werror,-Wunused-local-typedef]
    typedef void (*F)(U1, U2, U3);
                   ^
1 error generated.
```
Solution:
```
./waf configure --disable-werror
```

### NOTE WHEN WANT PyViz IN YOUR PROGRAM

Then activating the visualizer is a matter of enable the --vis waf option:
./waf configure —disable-werror
./waf --run myprogram --vis
Note: the --vis option only works if the program uses ns3::CommandLine to parse command-line arguments:

```
main(int argc, char *argv[])
{
   [...]
   CommandLine cmd;
   cmd.Parse (argc, argv);
   [...]
   Simulator::Run ();
 }
 ```

####Problems vith PyViz

Can't run because of not finding "LineDash"
https://stackoverflow.com/questions/52810243/ns33-29-python-visualiser-fails-when-i-try-to-execute-a-program

Try to replace the line in src/visualizer/visualizer/core.py on line 528 from:

GooCanvas.LineDash
to
GooCanvas.CanvasLineDash.newv 

 
### BUGS
 
 
-----UserWarning: PyGobject bug causing label position error; ------
should be fixed in PyGObject >= 3.29.1  warnings.warn("PyGobject
bug causing label position error; 
--------------------------------------------------------
Development libraries usually don't show up very well in the software center. 
Usually using apt-cache search will help here. So for example:

```
apt-cache search python gobject
```
Will show you all the packages related to python and gobject introspection.

https://askubuntu.com/questions/419945/how-does-one-install-pygobject-from-the-official-repository
 

### Issues

How to enable tap-bridge

