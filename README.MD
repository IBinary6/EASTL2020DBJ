
Now what is this? Yet another EASTL not-a-fork?

Well first of all these days it is [not possible](https://github.com/electronicarts/EASTL/issues/302) just to simply git pull the EASTL. So I had to download the source using vcpkg, do some local shenanigans, copy, build and run, and then push to this repository.

Why? In all of my innocence I had grand plans for EASTL use over "here". Alas. Soon, I have faced the reality. By 2020 EASTL has become (very) big and (not very) over engineered. Not to my liking at all.

Thus I have decided, for this repo, to:

- completely change the allocator design
  - that is the big one
- remove the EASTL specific containers
  - we have funny results with fixed_ bunch, they appears slower?
  - honestly we do not need containers that much after all

What will be left will surely be good and functional. EASTL team certainly knows how to C++. It is only sometimes like they have this urge to complicate things for no obvious reason whatsoever. As far as I can see from here.

I promise we will always try and inform EASTL guys if we have any relevant questions or puzzles to solve. Or if we think we can contribute to the mother ship in any way.

So it seems I have a lot of free time? I wish. We "here" are building WIN SVR components. We use Visual Studio 2019, and each project has the [/kernel switch](https://shorturl.at/gGMNO) present. That means no standard C++, not throw/try/catch keywords, no RAII and a such. 

So this is repo now Windows only? I hope not. But I have no Linux machine readily available. Whoever tests this on
Linux or Mac please do let me know. We will cook the CIRCLE CI setup after that.

Same is for VS Code build. If you think you can contribute your .vscode folder please come forward.

This is time consuming and ambitious plan. Stay tuned :wink:

Sep 2020
[DBJ](https://dbj.org/)
