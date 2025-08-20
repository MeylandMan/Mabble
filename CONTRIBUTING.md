# Contributing guidelines
This document gather all the guidelines to respect for contributing to the Mabble project. You can contribute on it mainly by pull requests and issues creation.

By correctly following all the guidelines below, your issue/PR will more likely to be taken to consideration.

## Issues
The greatest way to contribute to this project is just by creating an issue to point something that you want to add. 
Whenever you want to add an issue, always be sure that the issue doesn't already exists as [open](https://github.com/MeylandMan/Mabble/issues) or [closed](https://github.com/MeylandMan/Mabble/issues?q=is%3Aissue%20state%3Aclosed). 
This will be counted as duplicate and may be deleted right after his creation.

the issue section is used for bugs, feature or improvement proposals.

### Reporting a bug
When reporting a bug, make sure to give as much details as possible for me to replicate de bug such as images/videos, system specs, mabble version, etc.

**Note that you need to check if the bug is reproductible in a current version of Mabble.**

### Proposing a new feature / enchancement
> Note: The following points describe requirements for a proposal issue. A discussion, on the other hand, can be started in any form.

The only way you need to propose a feature/improvement is through issues.

Proposal issues are required to explain in technical detail how the suggested change should be implemented. 
It is also preferred that the submitter of a proposal is ready to implement it if it was approved. 
If you have a more general idea for a feature but are not well versed in Mabble's architecture or do not possess the necessary knowledge to implement it in the project, 
feel free to open a discussion instead of an issue (which is the only exception accepted to create a discussion about features/improvement).

**Note that the discussion once accepted, needs to be in form of an issue to keep easy track on this's feature/improvement process**

you need to wait for the feature to be accepted by the core developer of Mabble, for it to be implemented.

**Proposals should be made by opening an issue, not a pull request**. Don't fork this repository to open a proposal.


To have more chances to get an accepted feature proposal, you need to respect these simple rules:
- Only proposals that properly fill out the template will be considered. If the template is not filled out or is filled out improperly, it may be closed or even deleted.
- Please open one proposal per feature requested. Do not cram multiple feature requests in a single proposal, as this makes it harder to discuss features individually.
- Instead of just creating an issue on "how it'd be fun to" or "it'd would be helpful if",
you should always use the template to showcase clearly how this feature/improvement could change Mabble or his workflow

  - If you are still unsure about your feature, you could talk to the discussion section to improve it

- For your feature to be approved, other users need to be interested in your feature/improvements to add.
This could avoid some features you find comfortable but the entire community despise.
if the majority of the community refuse your modification proposal, it will be closed or even deleted.
(You can vote for an issue directly inside the main description of this issue's page. A thumb up (👍) for approved, and a thumb down (👎) for refused)

If your proposal was closed because the template was not filled out, then fill out the template and ask the person who closed the issue to re-open it.

If your proposal was closed as a duplicate and had a different approach to solving the problem described in the linked proposal, 
please comment in the linked proposal with your own idea. You don't need to copy-paste your whole proposal's text. Instead, 
rephrase the main ideas and add mockups if needed.

if your proposal was closed due to a lack of interest, try to captive more attention through discussions or other thirdparty community channels.
After that, ask the person who closed the issue to re-open it.

If your proposal was closed because a core developer determined that it was not worth pursuing and you feel that it was wrongly closed, 
then feel free to join the Mabble Lead Dev discussion and have a more in-depth discussion with the core developer about the feature.

### Steps of features proposal evaluation
Here's some details about how the core developer will be accepting or refusing proposals made. This also explain some deadlines about it.

First, the core developer needs to check if the rules above had been respected by you. if so, you can go to the next step. if not, the issue will be closed.

When proposing a feature through issues, you have a delay of **3 weeks** to gather enough people to have interest into your proposal.
The core developer can also accept this proposal within those delay if it gathered enough people to take into consideration or any other reasons.

at this step, everything will be analysed to check if the proposal is not too "out-of-reach" a realisable into the current scope.

The motto of this project is always to deal more with performance more than maintainability by following a 7:3 ratio. 
Those kind of feature/improvements are more likely to be accepted

Finally, the core developer needs to think if the feature is really going to improve the project in any way.

Once all of this are done, your issue will be active therefore, could be worked on.

## Contributing through pull requests
### Be mindful of your commits
Try to make simple PRs that handle one specific topic. Just like for reporting issues, 
it's better to open 3 different PRs that each address a different issue than one big PR with three commits. This makes it easier to review, approve, 
and merge the changes independently.

When updating your fork with upstream changes, please use ``git pull --rebase`` to avoid creating "merge commits". 
Those commits unnecessarily pollute the git history when coming from PRs.

Also try to make commits that bring the engine from one stable state to another stable state, i.e. if your first commit has a bug that you fixed in the second commit, 
try to merge them together before making your pull request. This includes fixing build issues or typos, adding documentation, etc.

This [Git style guide](https://github.com/agis/git-style-guide) also has some good practices to have in mind.

### Format your commit messages with readability in mind
The way you format your commit messages is quite important to ensure that the commit history and changelog will be easy to read and understand. 
A Git commit message is formatted as a short title (first line) and an extended description (everything after the first line and an empty separation line).

The short title is the most important part, as it is what will appear in the changelog or in the GitHub interface unless you click the "expand" button. 
Try to keep that first line under 72 characters, but you can go slightly above if necessary to keep the sentence clear.

It should be written in English, starting with a capital letter, and usually with a verb in past tense. A typical bugfix would start with "Fixed", 
while the addition of a new feature would start with "Added" or "Improved" for improvement. A prefix can be added to specify the project affected by the commit. Some examples:

- Added Vulkan swap chain
- removed OpenGL Vertex Array
- Mabble: Fixed ``RefCounter::Create()`` not correctly instantiating the object

If your commit fixes a reported issue, please include it in the description of the PR (not in the title, or the commit message) using one of the [GitHub closing keywords](https://docs.github.com/en/issues/tracking-your-work-with-issues/using-issues/linking-a-pull-request-to-an-issue) such as "Fixes #1234". 
This will cause the issue to be closed automatically if the PR is merged. Adding it to the commit message is easier, but adds a lot of unnecessary updates in the issue distracting from the thread.

> vague prefixes from commits names such as "Updated file.cpp" or "Misc" won't be accepted. 
Please, change the default commit name if you are using the github online editor or its drag-and-drop feature.

### Write unit test
When fixing a bug or contributing a new feature, we recommend including unit tests in the same commit as the rest of the pull request. 
Unit tests are pieces of code that compare the output to a predetermined expected result to detect regressions. 
Tests are compiled and run on GitHub Actions for every commit and pull request.

Pull requests that include tests are more likely to be merged, since we can have greater confidence in them not being the target of regressions in the future.

For bugs, the unit tests should cover the functionality that was previously broken. If done well, this ensures regressions won't appear in the future again. 
For new features, the unit tests should cover the newly added functionality, testing both the "success" and "expected failure" cases if applicable.

Feel free to contribute standalone pull requests to add new tests or improve existing tests as well.

The core developer of Mabble will handle the documentation himself. Please, do not create pull requests for that.

---
Thanks for your interest in contributing!

— Allan, Meyland
