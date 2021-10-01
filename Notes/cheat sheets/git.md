# My Git Cheat Sheet

### Initialization

1. `git config --global user.name "your_username"`: Sets up your username(should be the same as your username in Github/Gitlab)
   + You can also use `--local` if you don't want to change your global settings
2. `git config --global user.email "your_email@domain.com"`: Similar to the above command, for setting up your email
3. `git init`: Creates a new repo in the current directory
4. `git clone https://gitlab.com/owners_username/name_of_repo.git`: Clones an online repository (https)
5. 

### Inspection Commands

1. `git status`: Shows you how your current working environment is
2. `git diff folder1/folder2/file`: Shows you the most recent changes to the file located at `folder1/folder2/file`
3. `git config --global --list`: Shows your global configuration, including username, email, etc
   + Can also use `--local` to see local configurations
4. `git log --all --decorate --oneline --graph`: Shows the state and history of your repo in an intuitive way
   + You can create an alias for this useful command: `alias graph='git log --all --decorate --oneline --graph'`
5. `git remote -v`: Shows you your remotes and their associated addresses
6. `git log branch_name`: Shows the history (of commits) for a branch

### Commits

1. `git add file_name`: Adds a file to staging area, making it ready for a commit
   + `git add .` adds all the changes to the staging area
2. `git commit -m"Some comment for this commit"`: Commits the staged changes

### Branches

1. `git checkout branch_name`: Move to another branch
   + You can checkout a remote branch in a similar way. For instance `git checkout remote_name/remote_branch_name`, where `remote_name` is usually `origin`.
2. `git branch new_branch_name`: Creates a new branch
3. 

### Remotes

1. `git fetch remote_name`: Fetches latest changes from a remote(usually, `origin`)

   + This command will not affect your files and will only fetch information from a remote

   + In order to fetch a particular branch, use `git fetch remote_name branch_name`
   + In order to fetch everything from all your remotes, use `git fetch --all`

2. `git push remote_name local_branch_name:remote_branch_name`: Pushes the content of a local branch to a remote branch

   + If the name of your local and remote branches are the same, you can just write `git push remote_name branch_name`
   + Be cautious! `git push remote_name :remote_branch_name` will remove a branch from remote!
   + In the most simple case, our remote is `origin` and our branch is `master`; giving us the the famous `git push origin master` command!