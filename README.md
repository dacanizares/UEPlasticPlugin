Unreal Engine 4 Plastic Source Control Plugin
---------------------------------------------

[![release](https://img.shields.io/github/release/SRombauts/UE4PlasticPlugin.svg)](https://github.com/SRombauts/UE4PlasticPlugin/releases)

UE4PlasticPlugin is a simple Plastic Source Control Plugin for Unreal Engine 4

It is not intended to replace Plastic SCM GUI or command line.
It is a complementary tool improving efficiency in daily workflow.
It automates tracking of assets, bring common SCM tasks inside the Editor, and provide visual diffing of Blueprints.

![History Log window](Resources/UE4PlasticPlugin-History.png) 

### References

- [Source Control user interface](https://docs.unrealengine.com/latest/INT/Engine/UI/SourceControl/)
- [Source Control Inside Unreal Editor](https://docs.unrealengine.com/latest/INT/Engine/Basics/SourceControl/InEditor/)

### Quick setup

1. Your Unreal Engine 4.11.1 Game Project folder should be initialized
   into a workpace using the standard Plastic SCM GUI or cli.
2. Unzip the content of the plugin ZIP in the root of the Unreal Engine 4.11.1 project folder.
   That should create a "Plugins/" folder in it.
3. Launch Unreal Engine 4.11.1, click on the Source Control icon "Connect to Source", select "Plastic".

### Status

Alpha version 0.4.1 2016/05/11 :
- Windows only
- infrastructure : connect (cm version & cm status, optionnal configuration of the cli executable path)
- show current branch name in status text
- display status icons to show controled/checked-out/added/deleted/private/changed/ignored files
- display locked files
- add, duplicate, move/rename a file
- revert modifications of a file
- checkin a set of files with a multiline UTF-8 comment
- migrate an asset between two projects if both are using Plastic SCM
- delete file (but no way to checkin them, see known issues bellow)
- update workspace to latest head (Sync command)
- show history of a file
- visual diff of a blueprint against depot or between previous versions of a file
- initialize a new workspace to manage your UE4 Game Project.
- create an appropriate ignore.conf file as part as initialization
- make the initial commit
- also permit late creation of the ignore.conf file

#### What *cannot* be done presently (TODO list for v1.0, ordered by priority):
- solve a merge conflict on a blueprint
- tags: get labels (used for crash when the full Engine is under Plastic SCM)
- annotate: blame (used for crash when the full Engine is under Plastic SCM)
- Mac and Linux

#### Feature Requests (post v1.0)
- improve "status" efficiency by requesting status of the workspace root instead of file by file
- fire a global "status" command at startup (to populate the cache) to fix wrong context menu on content folders ("Mark for Add")
- add a top-menu "Sync/Update" instead of "Sync" on folder's context menu
- add a top-menu option to "undo all changes" in the project
- add a top-menu option to "undo unchanged only"
- add a "clean directory" or "checkin deleted files"
- add a setting to pass the --update option to "checkin"
- add a setting to tell UE if Plastic SCM is configured to use "read-only flags" like Perforce
- add support for partial checkin (like Gluon, for artists)

#### Bugs
.6 Checkout in a not up-to-date workspace: checkin fails silently.
.12 Revert "Unchanged only" does nothing.

#### Known issues:
- Error messages with accents are not handled (for instance connection error in French)
- the Editor does not show deleted files => no way to checkin them!
- the Editor does not show missing files
- the Editor does not show .uproject file
- a Move/Rename leaves a redirector file behind:
  renaming a Blueprint in Editor leaves a tracker file, AND modify too much the asset to enable Plastic to track its history through renaming
- the Editor does no show folder status and is not able to manage them
- reverting a Blueprint asset does not update content in Editor!
- Branch is not in the current Editor workflow (but on Epic Roadmap)
