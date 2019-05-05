# ezHostsFile
This program is used to unblock sites by adding their ip and url to /etc/hosts file.
**Currently only works in Linux OSes**
**This needs permission to write to hosts**

##Compilation

'cd src'
'gcc -o -lcurl main.c include/file/appendtofile.c include/curl/getip.c'

##Usage

'ezhostsfile *url*'
