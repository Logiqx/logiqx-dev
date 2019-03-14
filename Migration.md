# Migrating from CVS to Git

## Overview

### Introduction

This repository was originally tracked / versioned using [CVS](https://en.wikipedia.org/wiki/Concurrent_Versions_System), running under Windows.

The sections below detail how I went about migrating the repository to [Git](https://git-scm.com/) and pushing it to [GitHub](https://github.com/).

The migration was performed within a [Ubuntu](https://www.ubuntu.com/) bash shell, running under [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/about).

The main tools used were [cvs-fast-export](http://www.catb.org/~esr/cvs-fast-export/) and Git itself, referencing the [howto](http://www.catb.org/~esr/reposurgeon/dvcs-migration-guide.html) guide from [reposurgeon](http://www.catb.org/~esr/reposurgeon/).



### Approach

The approach was to export the original repository directly from CVSROOT and import it into Git.

The cvs-fast-export tool did a great job, exporting the legacy CVS repository as a Git fast-import file.

The process was largely automatic and mapping the committers / authors was the only minor complication.

The .git directory was then copied into the original project directory and local changes / additions reviewed.

Finally and once I was happy with everything the Git repository was pushed to GitHub.



## Pre-Requisites

### Installing cvs-fast-export

Install GCC:

```sh
mike@MIKE-ENVY:~$ sudo apt install gcc
```

Install make:

```sh
mike@MIKE-ENVY:~$ sudo apt install make
```

Install CVS:

```sh
mike@MIKE-ENVY:~$ sudo apt install cvs
```

Install asciidoc:

```sh
mike@MIKE-ENVY:~$ sudo apt-get update
mike@MIKE-ENVY:~$ sudo apt install asciidoc
```

Install cvs-fast-export:

```bash
mike@MIKE-ENVY:~/cvs-fast-export-1.45$ make
...
mike@MIKE-ENVY:~/cvs-fast-export-1.45$ make check
...
mike@MIKE-ENVY:~/cvs-fast-export-1.45$ sudo make install
[sudo] password for mike:
install -d "/usr/local/bin"
install cvs-fast-export cvssync cvsconvert "/usr/local/bin"
install -d "/usr/local/share/man/man1"
install -m 644 cvs-fast-export.1 "/usr/local/share/man/man1"
install -m 644 cvssync.1 "/usr/local/share/man/man1"
install -m 644 cvsconvert.1 "/usr/local/share/man/man1"
```



### Installing Dos2Unix

This tool is needed for conversion of CR/LF to LF:

```bash
mike@MIKE-ENVY:~$ sudo apt install dos2unix
```



## Preparation

### Converting CR/LF to LF

Ensure that all text files in the existing project directory are converted from CR/LF to LF:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ find . -type f -exec dos2unix {} \;
```

Note: Binary files are automatically skipped by the dos2unix command.

Check for any unexpected artefacts as a result of the above conversion:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ find . -type f -exec file {} \; | grep ASCII | grep "line terminators"
./DatUtil/tst/RAINE Listinfo.dat: Non-ISO extended-ASCII text, with CRLF, CR, NEL line terminators, with escape sequences
./Limited Edition/IPMask/_test.bat: ASCII text, with no line terminators
```

Fix the two issues identified above:

+ RAINE Listininfo,dat needs to be re-created as it was damaged by dos2unix

+ IPMask/_test.bat never had the final CR/LF so add it using a text editor and run it through dos2unix



## Migration

### Exporting from CVSROOT

Export the existing repository / module from CVSROOT using cvs-fast-export:

```sh
mike@MIKE-ENVY:/mnt/c/Logiqx/CVSROOT$ find Dev | cvs-fast-export -p >../Dev.fi
2019-03-13T13:50:24Z: Reading file list...done, 5096.669KB in 145 files (0.069sec)
2019-03-13T13:50:24Z: Analyzing masters with 8 threads...done, 1263 revisions (1.368sec)
2019-03-13T13:50:26Z: Make DAG branch heads...145 of 145(100%)    (0.000sec)
2019-03-13T13:50:26Z: Sorting...done  (0.000sec)
2019-03-13T13:50:26Z: Compute branch parent relationships...2 of 2(100%)    (0.000sec)
2019-03-13T13:50:26Z: Collate common branches...2 of 2(100%)    (0.008sec)
2019-03-13T13:50:26Z: Find tag locations...99 of 99(100%)    (0.037sec)
2019-03-13T13:50:26Z: Compute tail values...done  (0.000sec)
2019-03-13T13:50:26Z: Generating snapshots...done (0.211sec))
2019-03-13T13:50:26Z: Saving in fast order: done (0.059sec))
cvs-fast-export: no commitids before 2010-10-28T20:16:41Z.
       after parsing:   1.439   2064KB
after branch collation: 1.487   6212KB
               total:   1.757   10096KB
505 commits/47.451M text, 932 atoms at 287 commits/sec.
```



### Mapping Committers / Authors

"Mike" and "cvs-fast-export" were mapped to "Logiqx" using the following hack:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx$ strings Dev.fi | grep 'committer' | awk '{print $1, $2, $3}' | sort -u
committer cvs-fast-export <cvs-fast-export>
committer Mike <Mike>
mike@MIKE-ENVY:/mnt/c/Logiqx$ sed 's/committer .* <.*>/committer Logiqx <software@mikeg.me.uk>/' Dev.fi >Dev.tmp.fi
mike@MIKE-ENVY:/mnt/c/Logiqx$ strings Dev.tmp.fi | grep 'committer' | awk '{print $1, $2, $3}' | sort -u
committer Logiqx <software@mikeg.me.uk>
```

Note: I'm not 100% happy about hacking the fast import file but it seemed to work ok!



### Importing to Git

The "fast import" was performed using the standard Git client:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx$ git init Dev.tmp
Initialized empty Git repository in /mnt/c/Logiqx/Dev.tmp/.git/
mike@MIKE-ENVY:/mnt/c/Logiqx$ cd Dev.tmp
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp$ git fast-import <../Dev.tmp.fi
git-fast-import statistics:
---------------------------------------------------------------------
Alloc'd objects:       5000
Total objects:         3215 (        94 duplicates                  )
      blobs  :         1164 (        91 duplicates        991 deltas of       1080 attempts)
      trees  :         1546 (         3 duplicates       1244 deltas of       1434 attempts)
      commits:          505 (         0 duplicates          0 deltas of          0 attempts)
      tags   :            0 (         0 duplicates          0 deltas of          0 attempts)
Total branches:         101 (       100 loads     )
      marks:        1048576 (      1759 unique    )
      atoms:            141
Memory total:          2344 KiB
       pools:          2110 KiB
     objects:           234 KiB
---------------------------------------------------------------------
pack_report: getpagesize()            =       4096
pack_report: core.packedGitWindowSize = 1073741824
pack_report: core.packedGitLimit      = 8589934592
pack_report: pack_used_ctr            =       4202
pack_report: pack_mmap_calls          =        102
pack_report: pack_open_windows        =          1 /          1
pack_report: pack_mapped              =    1566038 /    1566038
---------------------------------------------------------------------
```



### Checking Out from Git

Checkout all of the files and check the author(s):

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp$ git checkout
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp$ git status
On branch master
nothing to commit, working directory clean
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp$ git log | grep Author | sort -u
Author: Logiqx <software@mikeg.me.uk>
```



### Comparing Project Directories

A simple directory comparison was used to compare the CVS and Git project directories:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx$ diff -rq Dev Dev.tmp
Files Dev/DatLib/datafile.dtd and Dev.tmp/DatLib/datafile.dtd differ
...
Files Dev/DatUtil/tst/RAINE Listinfo.dat and Dev.tmp/DatUtil/tst/RAINE Listinfo.dat differ
...
mike@MIKE-ENVY:/mnt/c/Logiqx$ diff -rw Dev Dev.tmp | egrep -v 'Only in .* CVS|obj|exe'
diff -rw Dev/DatLib/datafile.dtd Dev.tmp/DatLib/datafile.dtd
11,12c11,12
<    $Revision: 1.5 $
<    $Date: 2008/10/28 21:39:16 $
---
>    $Revision: 1.4 $
>    $Date: 2008/04/15 20:42:06 $
Only in Dev/DatUtil: dats
Only in Dev/DatUtil: datutil.dat
Only in Dev/DatUtil: scan
Only in Dev/DatUtil: switches.txt
Only in Dev/DatUtil/tst: AAE All Game Roms List.txt
Only in Dev/DatUtil/tst: m1.xml
Only in Dev/DatUtil/tst: mame.xml
Only in Dev/DatUtil/tst: mess.old.xml
Only in Dev/DatUtil/tst: mess.xml
Only in Dev: grep.sh
Only in Dev/Limited Edition/IPMask: inet32ut
Only in Dev/Limited Edition/IPMask: ipmask.log
Only in Dev/Limited Edition/IPMask: _test.bat
Only in Dev.tmp/Limited Edition: m1sha1
Only in Dev/Limited Edition: M1SHA1
Only in Dev/MAMEDiff: tst
Only in Dev: Migration.md
Only in Dev/ROMInfo: rominfo.log
Only in Dev/ZIPIdent: zipident.dat
mike@MIKE-ENVY:/mnt/c/Logiqx$ diff -rq Dev Dev.tmp | grep -i m1
Only in Dev/DatUtil/tst: m1.xml
Only in Dev.tmp/Limited Edition: m1sha1
Only in Dev/Limited Edition: M1SHA1
```

Note: With the exception of the revision change, everything in Git matched the original project directory.



### Renaming the M1SHA1 Directory

Rename the M1SHA1 directory so that it has the intended case:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp/Limited Edition$ mv m1sha1 M1SHA1
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp/Limited Edition$ git add .
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp/Limited Edition$ git status
On branch master
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

        renamed:    m1sha1/m1.xml -> M1SHA1/m1.xml
        renamed:    m1sha1/m1sha1.txt -> M1SHA1/m1sha1.txt
        renamed:    m1sha1/makefile -> M1SHA1/makefile
        renamed:    m1sha1/src/m1sha1.c -> M1SHA1/src/m1sha1.c
        renamed:    m1sha1/src/m1sha1.h -> M1SHA1/src/m1sha1.h

mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp/Limited Edition$ git commit -m "Rename m1sha1 to M1SHA1"
[master b187d38] Rename m1sha1 to M1SHA1
 5 files changed, 0 insertions(+), 0 deletions(-)
 rename Limited Edition/{m1sha1 => M1SHA1}/m1.xml (100%)
 mode change 100755 => 100644
 rename Limited Edition/{m1sha1 => M1SHA1}/m1sha1.txt (100%)
 mode change 100755 => 100644
 rename Limited Edition/{m1sha1 => M1SHA1}/makefile (100%)
 mode change 100755 => 100644
 rename Limited Edition/{m1sha1 => M1SHA1}/src/m1sha1.c (100%)
 mode change 100755 => 100644
 rename Limited Edition/{m1sha1 => M1SHA1}/src/m1sha1.h (100%)
 mode change 100755 => 100644
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev.tmp/Limited Edition$ git status
On branch master
nothing to commit, working directory clean
```



### Switching from CVS to Git

Remove the CVS directories and copy the Git repository into the project directory.

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx$ find Dev -type d -name CVS -exec rm -fr {} \;
...
mike@MIKE-ENVY:/mnt/c/Logiqx$ cp -p Dev.tmp/.gitignore Dev/
mike@MIKE-ENVY:/mnt/c/Logiqx$ cp -rp Dev.tmp/.git Dev/
```



## Tidy Up

### Configuring the Git User

Prior to committing any changes to Git the user name and e-mail need to be specified:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx$ git config --global user.name "Logiqx"
mike@MIKE-ENVY:/mnt/c/Logiqx$ git config --global user.email "software@mikeg.me.uk"
```



### Reviewing Local Changes

Use the GIt "status" and "diff" commands to identify local changes:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git status
On branch master
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   DatLib/datafile.dtd

Untracked files:
  (use "git add <file>..." to include in what will be committed)

        DatUtil/dats/
        DatUtil/scan/
        DatUtil/switches.txt
        DatUtil/tst/AAE All Game Roms List.txt
        DatUtil/tst/m1.xml
        DatUtil/tst/mame.xml
        DatUtil/tst/mess.xml
        Limited Edition/IPMask/.gitignore
        MAMEDiff/tst/
        Migration.md
        README.md
        ROMInfo/.gitignore
        ZIPIdent/.gitignore

no changes added to commit (use "git add" and/or "git commit -a")
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git diff
diff --git a/DatLib/datafile.dtd b/DatLib/datafile.dtd
index 7e71175..68c980f 100755
--- a/DatLib/datafile.dtd
+++ b/DatLib/datafile.dtd
@@ -8,8 +8,8 @@
    PUBLIC "-//Logiqx//DTD ROM Management Datafile//EN"
    SYSTEM "http://www.logiqx.com/Dats/datafile.dtd"

-   $Revision: 1.4 $
-   $Date: 2008/04/15 20:42:06 $
+   $Revision: 1.5 $^M
+   $Date: 2008/10/28 21:39:16 $^M

 -->
```



### Committing the Revision Change

The revision and date in datafile.dtd were committed as follows:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git commit -m "Commit revision change" DatLib/datafile.dtd
[master 6d505f3] Commit revision change
 1 file changed, 2 insertions(+), 2 deletions(-)
 mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git diff
```



### Handling Untracked Files

Untracked files were either removed, committed to Git or added to .gitignore files:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git status
On branch master
Your branch is ahead of 'origin/master' by 2 commits.
  (use "git push" to publish your local commits)
Untracked files:
  (use "git add <file>..." to include in what will be committed)

        DatUtil/dats/
        DatUtil/datutil.dat
        DatUtil/scan/
        DatUtil/switches.txt
        DatUtil/tst/AAE All Game Roms List.txt
        DatUtil/tst/m1.xml
        DatUtil/tst/mame.xml
        DatUtil/tst/mess.old.xml
        DatUtil/tst/mess.xml
        Limited Edition/IPMask/_test.bat
        Limited Edition/IPMask/inet32ut/
        Limited Edition/IPMask/ipmask.log
        MAMEDiff/tst/
        ROMInfo/rominfo.log
        ZIPIdent/zipident.dat
        grep.sh
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ ... one-off activities ...
```



### Final Check 

Check that the repository is clean:

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git status
On branch master
nothing to commit, working directory clean
```



## Publication

### Pushing the Repo to GitHub

```bash
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git remote add origin https://github.com/Logiqx/logiqx-dev.git
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git push -u origin --all
Username for 'https://github.com': Logiqx
Password for 'https://Logiqx@github.com':
Counting objects: 3318, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (1049/1049), done.
Writing objects: 100% (3318/3318), 4.99 MiB | 298.00 KiB/s, done.
Total 3318 (delta 2262), reused 3205 (delta 2235)
remote: Resolving deltas: 100% (2262/2262), done.
To https://github.com/Logiqx/logiqx-dev.git
...
mike@MIKE-ENVY:/mnt/c/Logiqx/Dev$ git status
On branch master
Your branch is up-to-date with 'origin/master'.
nothing to commit, working directory clean
```

