Contributing to the Mediarizer Project
* [1. Introduction](#1-introduction)
* [2. Contributing code via GitHub](#2-contributing-code-via-github)
* [3. Reporting Bugs](#5-reporting-bugs)

# 1. Introduction #

We welcome any help, for example contributing lens data (images), code contributions and bug reports.

# 2. Contributing code via GitHub #

Code contributions can be performed via *pull requests* (PR) on GitHub (if you cannot or do not want to use GitHub.
As a rule-of-thumb:

- PRs should be kept at a manageable size. Try to focus on just one goal per PR. If you find yourself doing several things in a PR that were not expected,
  then try to split the different tasks into different PRs.
- Commits should always change a *single* logical unit so that cherry-picking & reverting is simple.
- Commit messages should be as informative and concise as possible. The first line of the commit message should be < 80 characters and
  describe the commit briefly. If the 80 characters are too short for a summary, then consider splitting the commit. Optionally, add one blank line
  below the short summary and write a more detailed explanation if necessary.

Below we outline the recommended steps in the code contribution workflow. We use `your-username` to refer to your username on GitHub, `mediarizer_upstream` is used when we
set the upstream remote repository for Mediarizer (we could have picked any name but try to avoid already used names like, in particular, `origin` and `master`), and
we use the name `my-new-feature` for the branch that we create (e.g., the branch name should reflect the code change being made).

**Important**: If your PR lives for a long time, then don't press the button _Update branch_ in the Pull Request view, instead follow the steps below, as
that avoids additional merge commits.

Once you have a GitHub login:

1. Fork the Mediarizer git repository to your GitHub account by pressing the _Fork_ button at: [https://github.com/keybraker/Mediarizer](https://github.com/keybraker/Mediarizer)

2. Then start a terminal (or use your favorite git GUI app) and clone your fork of the Mediarizer repo:

        $ git clone https://github.com:your-username/Mediarizer.git
        $ cd Mediarizer

3.  Add a new remote pointing to upstream Mediarizer repository:

        $ git remote add mediarizer_upstream https://github.com/keybraker/Mediarizer.git

    and verify that you have the two remotes configured correctly:

        $ git remote -v
        mediarizer_upstream  https://github.com/keybraker/Mediarizer.git (fetch)
        mediarizer_upstream  https://github.com/keybraker/Mediarizer.git (push)
        origin  https://github.com/your-username/Mediarizer.git (fetch)
        origin  https://github.com/your-username/Mediarizer.git (push)

4. Next, create a branch for your PR from `mediarizer_upstream/master` (which we also need to fetch first):

        $ git fetch mediarizer_upstream master
        $ git checkout -b my-new-feature mediarizer_upstream/master --no-track

    NB: This is an important step to avoid draging in old commits!

5. Configure the project and check that it builds (if not, please report a bug):

        $ rm -rf build
        $ mkdir build && cd build
        $ cmake -DCMAKE_BUILD_TYPE=Release ..
        $ make

6. Now, make your change(s), add tests for your changes, and commit each change:

        ...

        $ git commit -m "Commit message 1"

        ...

        $ git commit -m "Commit message 2"

7. Push the changes to your fork on GitHub:

        $ git push origin my-new-feature

8. Create the PR by pressing the _New pull request_ button on: `https://github.com/your-username/Mediarizer`. Please select the option "Allow edits from maintainers" as outlined [here](https://help.github.com/en/articles/allowing-changes-to-a-pull-request-branch-created-from-a-fork).

9. Now wait for an Mediarizer project member(s) to respond to your PR. Follow the discussion on your PR at [GitHub](https://github.com/keybraker/Mediarizer/pulls).
    You may have to do some updates to your PR until it gets accepted.

10. After the PR has been reviewed you must _rebase_ your repo copy or merge with dev since there may have been several changes to the upstream repository.

    Switch to your branch again

        $ git checkout my-new-feature

    And rebase it on top of master:

        $ git pull --rebase mediarizer_upstream master

    When you perform a rebase the commit history is rewritten and, therefore, the next time you try to push your branch to your fork repository you will need to use
    the `--force-with-lease` option:

        $ git push --force-with-lease

# 3. Reporting Bugs #

Bugs should be reported by creating Issues on GitHub.
> before reporting a bug first check the issue list if the bug is already known<br>
> If you cannot find any previous bug report, create a new Issue. When reporting a bug try to describe the problem in as much detail as possible and if the bug is triggered by an input file then attach that file to the GitHub issue if possible.
