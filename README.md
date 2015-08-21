# Z Synth Sampler Editor
ZSFEdit is an sampler editor for ZSF compatible Z Synth PCM synthesizers.
## Overview
* Graphical wave editor
* Basic sound editor (crop, fade)
* Loop editor (manual and auto search)
* Import from most audio format
* SysEx dump/update
## How to build
1. Download source

```
# git clone https://github.com/hzoli17/ZSFEdit.git
Cloning into 'ZSFEdit'...
remote: Counting objects: 55, done.
remote: Compressing objects: 100% (47/47), done.
remote: Total 55 (delta 14), reused 47 (delta 6), pack-reused 0
Unpacking objects: 100% (55/55), done.
Checking connectivity... done.
```
or download from GitHub page in ZIP format

2. Extract and enter to directory
If you download with GIT:
```
# cd ZSFEdit
```
If you downloaded from webpage in ZIP format:
enter to download directory and uncompress archive.
If you like to uncompress in UN*X system: 
```
# unzip ZSFEdit-master.zip
```
After enter to directory
```
# cd ZSFEdit-master
```

3. Build source

```
# qmake
# make
```

4. Enjoy

```
# ./ZSFEdit
```

![Interface](http://79.120.211.36/ZSF2.png) 
