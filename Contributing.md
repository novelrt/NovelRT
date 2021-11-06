# Contributing to NovelRT

:+1::tada: First off, thank you for taking the time to contribute! We really appreciate it! :tada::+1:

The following is a set of guidelines for contributing to NovelRT, which is hosted in the [NovelRT Organization](https://github.com/novelrt) on GitHub. These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document in a pull request.

#### Table Of Contents

[Code of Conduct](#code-of-conduct)

[I don't want to read this whole thing, I just have a question!!!](#i-dont-want-to-read-this-whole-thing-i-just-have-a-question)

[What should I know before I get started?](#what-should-i-know-before-i-get-started)
  * [Design Decisions](#design-decisions)

[How Can I Contribute?](#how-can-i-contribute)
  * [Reporting Bugs](#reporting-bugs)
  * [Suggesting Enhancements](#suggesting-enhancements)
  * [Your First Code Contribution](#your-first-code-contribution)
  * [Pull Requests](#pull-requests)

[Additional Notes](#additional-notes)
  * [Issue and Pull Request Labels](#issue-and-pull-request-labels)

## Code of Conduct

This project and everyone participating in it is governed by the [NovelRT Contributor Code of Conduct](CODE_OF_CONDUCT.md). By participating, you are expected to uphold this code. Please report unacceptable behavior to [admin@novelrt.dev](mailto:admin@novelrt.dev) or message one of the maintainers on Discord.

## I don't want to read this whole thing I just have a question!!!

> **Note:** *Please don't file an issue to ask a question.* You'll get faster results by using the resources below.

We have an official message board on Github that you can utilize, or you can reach us on Discord where the community chimes in with helpful advice if you have questions.

* [Github Discussions, NovelRT](https://github.com/novelrt/NovelRT/discussions)
* [NovelRT Discord Server](https://discord.gg/novelrt)

## What should I know before I get started?

### Design Decisions

When we make a decision in how we maintain the project and what we can or cannot support, we will typically announce this as part of a milestone on [Github](https://github.com/novelrt/NovelRT/milestones). If you have a question around what is being worked on by the NovelRT team, check to see if it is documented there. If it is *not* documented there, please open a new topic on [Github Discussions](https://github.com/novelrt/NovelRT/discussions) or [Discord](https://discord.gg/novelrt) and ask your question.

## How Can I Contribute?

### Reporting Bugs

This section guides you through submitting a bug report for NovelRT. Following these guidelines helps maintainers and the community understand your report :pencil:, reproduce the behavior :computer: :computer:, and find related reports :mag_right:.

Before creating bug reports, please check [this list](#before-submitting-a-bug-report) as you might find out that you don't need to create one. We currently do not have a bug report template, so when you are creating a bug report, please [include as many details as possible](#how-do-i-submit-a-good-bug-report). 

> **Note:** If you find a **Closed** issue that seems like it is the same thing that you're experiencing, open a new issue and include a link to the original issue in the body of your new one.

#### Before Submitting A Bug Report

* Most importantly, check if you can reproduce the problem in the latest version of NovelRT.
* **Determine which repository the problem should be reported in**. If it is specifically related to the NovelRT engine core, its samples, or its Interop layer, it should be reported here.
* **Perform a [cursory search](https://github.com/novelrt/NovelRT/issues)** to see if the problem has already been reported. If it has **and the issue is still open**, add a comment to the existing issue instead of opening a new one.

#### How Do I Submit A (Good) Bug Report?

Bugs are tracked as [GitHub issues](https://guides.github.com/features/issues/). After you've determined which repository your bug is related to, create an issue on that repository following the steps below.

Explain the problem and include additional details to help maintainers reproduce the problem:

* **Use a clear and descriptive title** for the issue to identify the problem.
* **Describe the exact steps which reproduce the problem** in as many details as possible. For example, start by explaining how you configured NovelRT, e.g. which command exactly you used in the terminal, or how you built NovelRT otherwise. When listing steps, **don't just say what you did, but explain how you did it**. For example, if you built NovelRT using CMake, explain if you used Windows Command Prompt / Linux Terminal / Powershell, or a Developer Tools for VS window, and if so which version?
* **Provide specific examples to demonstrate the steps**. Include links to files or GitHub projects, or copy/pasteable snippets, which you use in those examples. If you're providing snippets in the issue, use [Markdown code blocks](https://help.github.com/articles/markdown-basics/#multiple-lines).
* **Describe the behavior you observed after following the steps** and point out what exactly is the problem with that behavior.
* **Explain which behavior you expected to see instead and why.**
* **Include screenshots and/or animated GIFs if applicable** which show you following the described steps and clearly demonstrate the problem. 
* **If the problem wasn't triggered by a specific action**, describe what you were doing before the problem happened and share more information using the guidelines below.

Provide more context by answering these questions:

* **Did the problem start happening recently** (e.g. after updating to the latest build of NovelRT) or was this always a problem?
* If the problem started happening recently, **can you reproduce the problem in an older build of NovelRT?** What's the most recent build/commit SHA in which the problem doesn't happen? 
* **Can you reliably reproduce the issue?** If not, provide details about how often the problem happens and under which conditions it normally happens.
* What area of NovelRT is the problem occurring in? (e.g. Is it Input related? Is it related to Rendering or Windowing? etc)

Include details about your configuration and environment:

* **Which build of NovelRT are you using?**
* **What's the name and version of the OS you're using**?
* **Was this pre-built? If not, what compiler was NovelRT built with?**
* **Are you running NovelRT in a virtual machine?** If so, which VM software are you using and which operating systems and versions are used for the host and the guest?
* **Are you using NovelRT with multiple monitors?** If so, can you reproduce the problem when you use a single monitor?
* **Which locale/region is your OS configured to use?**

#### Invalid Reports

While we understand that not every issue may get resolved, we have a zero-tolerance policy for issues that fall under the following categories:

* Spam
* Hateful/discriminatory language
* Repeatedly reported non-issue

Please note that while we will do our best to filter out these types of submissions, they may still pop up from time to time. If you notice that one of these types of issues are opened in _any_ of the NovelRT organisation's repositories, please e-mail [admin@novelrt.dev](mailto:admin@novelrt.dev) or message one of the maintainers in Discord. _Furthermore, any attempt to open an issue that falls under the above categories may result in disiplinary action by the NovelRT team up to and including a ban from interacting with the NovelRT repository (and other related repositories within the NovelRT organisation)_.

### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for NovelRT, including completely new features and minor improvements to existing functionality. Following these guidelines helps maintainers and the community understand your suggestion :pencil: and find related suggestions :mag_right:.

Before creating enhancement suggestions, please check [this list](#before-submitting-an-enhancement-suggestion) as you might find out that you don't need to create one. When you are creating an enhancement suggestion, please [include as many details as possible](#how-do-i-submit-a-good-enhancement-suggestion). 

#### Before Submitting An Enhancement Suggestion

* **Check if there's already [another repo](https://github.com/novelrt) which provides that enhancement.** _Note: NovelRT is still in its infancy, so this may not show much currently as we continue to enhance the engine core_.
* **Determine which repository the enhancement should be suggested in.**
* **Perform a [cursory search](https://github.com/novelrt/NovelRT/issues)** to see if the enhancement has already been suggested. If it has, add a comment to the existing issue instead of opening a new one.

#### How Do I Submit A (Good) Enhancement Suggestion?

Enhancement suggestions are tracked as [GitHub issues](https://guides.github.com/features/issues/). After you've determined which repository your enhancement suggestion is related to, create an issue on that repository and provide the following information:

* **Use a clear and descriptive title** for the issue to identify the suggestion.
* **Provide a step-by-step description of the suggested enhancement** in as many details as possible.
* **Provide specific examples to demonstrate the steps**. Include copy/pasteable snippets which you use in those examples, as [Markdown code blocks](https://help.github.com/articles/markdown-basics/#multiple-lines).
* **Describe the current behavior** and **explain which behavior you expected to see instead** and why.
* **Include screenshots and animated GIFs** which help you demonstrate the steps or point out the part of NovelRT which the suggestion is related to, if possible. (We understand that sometimes code changes can't be shown with a screenshot :sweat_smile:)
* **Explain why this enhancement would be useful** to most NovelRT users as core functionality and isn't something that can or should be implemented as a community plugin.
* **List some other game engines / examples where this enhancement exists (_if applicable_).**
* **Specify the name and version of the OS you're using.**

### Your First Code Contribution

Unsure where to begin contributing to NovelRT? You can start by looking through these `good first issue` and `help wanted` issues:

* [Good first issues](https://github.com/novelrt/NovelRT/issues?q=is%3Aopen+is%3Aissue+label%3A%22good+first+issue%22) - issues which should only require a few lines of code, and a test or two.
* [Help wanted issues](https://github.com/novelrt/NovelRT/issues?q=is%3Aopen+is%3Aissue+label%3A%22help+wanted%22) - issues which should be a bit more involved than `good first issues`.

Both issue lists are sorted by total number of comments. While not perfect, number of comments is a reasonable proxy for impact a given change will have.

#### Local development

For instructions on how to get started with local development of NovelRT, see the following sections in [the engine's README](https://github.com/novelrt/NovelRT#getting-started-with-novelrt).

### Pull Requests

The process described here has several goals:

- Maintain NovelRT's quality
- Fix problems that are important to users
- Engage the community in working toward the best possible NovelRT
- Enable a sustainable system for NovelRT's maintainers to review contributions

Please follow these steps to have your contribution considered by the maintainers:

1. Ensure that the title describes the overall enhancement/fix that is being provided.
2. The description should summarise the changes being made, and should call out what area(s) of the engine is being affected.
3. Follow the styleguide as provided by our [`.clang-format` file](https://github.com/novelrt/NovelRT/blob/main/.clang-format). (Our CI will assist you if you are unable to proactively do so, and will provide a git patch to fix most formatting issues, however this is not perfect and should not be guaranteed.)
4. The pull request that is opened should be [linked to a corresponding issue](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue#linking-a-pull-request-to-an-issue-using-a-keyword).
5. Once a pull request is opened, if you have not done so already you will be asked to sign our Contributor License Agreement (CLA).
5. After you submit your pull request, verify that all [status checks](https://help.github.com/articles/about-status-checks/) are passing <details><summary>What if the status checks are failing?</summary>If a status check is failing, and you believe that the failure is unrelated to your change, please leave a comment on the pull request explaining why you believe the failure is unrelated. A maintainer will re-run the status check for you. If we conclude that the failure was a false positive, then we will open an issue to track that problem with our status check suite.</details>

While the prerequisites above must be satisfied prior to having your pull request reviewed, the reviewer(s) may ask you to complete additional design work, tests, or other changes before your pull request can be ultimately accepted. Also, please note that under the circumstances listed below, a pull request _may_ be rejected with/without further recourse by the NovelRT team for the following:

* Creating a pull request without an open issue (**_this is limited to contributors only - outside collaborators and maintainers are permitted within reason_**).
* Creating a pull request that purposefully breaks functionality / alters functionality in a negative manner
* Creating a pull request to introduce spam into the repository

_Attempts to perform the actions called out above will result in disiplinary action by the NovelRT team up to and including a ban from interacting with the NovelRT repository (and other related repositories within the NovelRT organisation)_.

## Additional Notes

### Issue and Pull Request Labels

This section lists the labels we use to help us track and manage issues and pull requests. Most labels are used across all NovelRT repositories, but some are specific to `novelrt/NovelRT`.

[GitHub search](https://help.github.com/articles/searching-issues/) makes it easy to use labels for finding groups of issues or pull requests you're interested in. For example, you might be interested in [open issues across NovelRT that were approved by the team](https://github.com/novelrt/NovelRT/issues?q=is%3Aopen+is%3Aissue+label%3A%22dev+team+approved%22) or perhaps [open pull requests in `novelrt/NovelRT` which haven't been reviewed yet](https://github.com/novelrt/NovelRT/pulls?q=is%3Apr+is%3Aopen+review%3Anone). We encourage you to read about [other search filters](https://help.github.com/articles/searching-issues/) which will help you write more focused queries.

The labels are loosely grouped by their purpose, but it's not required that every issue has a label from every group or that an issue can't have more than one label from the same group.

Please open an issue on `novelrt/NovelRT` if you have suggestions for new labels, and if you notice some labels are missing on some repositories, then please open an issue on that repository.


<sub><sup>_This `Contributing.md` guide is adapted from the contribution guide provided by [Atom](https://github.com/atom/atom/blob/master/CONTRIBUTING.md) under the MIT License._</sup></sub>