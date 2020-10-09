
![results_2020_oct](./media/2020_OCT_screen.png)

## Now what is this? Yet another EASTL, not-a-fork?

Well first of all these days it is [not possible](https://github.com/electronicarts/EASTL/issues/302) just to simply git pull the EASTL. So I had to download the source using vcpkg. Then I did some local shenanigans, some copies, builds and runs; and then pushed the result to this repository.

Why? In all of my innocence I had grand plans for EASTL use over "here". Alas. Soon, I have faced the reality. By 2020 EASTL has become big and over engineered. Not to my liking at all. Thus.

### I have decided to:

- completely change the allocator design
  - that is done
- remove the EASTL specific containers
  - we have funny thoughts about the fixed_ bunch
      - fixed_ is ok for small-ish sizes having standard interface
      - but for that we use native arrays, also because of the kind of the projects
      - but also because we do seriously like using C11 + VLA declarations
      ```cpp
      typedef point3d(*pointer_to_matrix)[3][3];
      pointer_to_matrix pm_ = (pointer_to_matrix)
      malloc( sizeof(point3d[3][3]) );
      ```
  - honestly, we do not need containers that much after all, beside string and vector of course
      - we are very careful to minimize the C++ string usage

What is left is good and functional. But understand this: EASTL team certainly knows how to C++. I promise we will always try and inform EASTL guys if we have any relevant questions or puzzles to solve. Or if we think we can contribute to the mother ship in any way.

So it seems I have a lot of free time? I wish. We "here" are building WIN SVR components. We use Visual Studio 2019, and each project has, among other limitations, no exceptions, no RTTI, and such. How will this repo fit in there we shall see. Soon.

So is this repo now Windows only? I hope not. But I have no Linux machine readily available. Whoever tests this on Linux or Mac please do let me know. We will cook the CIRCLE CI setup after that.

Same is for VS Code build. If you think you can contribute your .vscode folder please come forward.

This is time consuming and ambitious plan for one person team. Stay tuned :wink:

## Some explanations

- In the source, seek the `dbj` namespace for news and changes.
- test folder contains Visual Studio solution. Start snooping from there
- `dbj_allocator.cpp` and `<EASTL/allocator.h>` are the files with most of the new stuff
- test/infrastructure  common contains `dbj_common.h`, this is where "everything" is included for testing which is in `testing_sampling.cpp`.

## Performance sampling: EASTL vs MS STL

- when we test, c++ exceptions are always off
     - MS STL replaces them with [SEH](https://docs.microsoft.com/en-us/cpp/cpp/structured-exception-handling-c-cpp?view=vs-2019)
     - EASTL does its own assert, which results in `__debugbreak()`
- RTTI we keep always off, too
- Road Map : in case of Structured Exception raised and caught, minidump is generated, and finally user is informed on its full path.
- 32 bit builds we ignore, as ever
- Hint: in debug builds MS STL is indeed rather slow, but in release builds it is not


Enjoy

Sep/Oct  2020
[DBJ](https://dbj.org/)
