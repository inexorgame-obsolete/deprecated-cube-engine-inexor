
# Inexor media repos

This folder hosts the different media repos.

Since we split data files from the code files for using Git with less waiting time, we have 2+ repositories now for a single Inexor game.


In case of a release the folder should already be filled with the folders `core`, `additional` (and maybe `playground`),
while `core` is the only required folder and exact spelling does not matter for any folder in here.

If this folder is empty, you'll need to bring back the data repositories in here.

Therefore, invoke:  

`git clone "https://github.com/inexor-game/data" core` (required)  
`git clone "https://github.com/inexor-game/data-additional" additional` (optional)  
`git clone "https://github.com/inexor-game/data-playground" playground` (optional)  

**inside this folder**.
