#Learning: 

Not knowing what the task wanted from me in Part2 by saying "find another way to keep your worry levels manageable", I went to reddit for a hint. There, I saw someone drop the word "Chinese Remainder Theorem", so I googled around to check for it (Geeks for Geeks had some nice articles). It didn't seem to directly apply to the situation, but it gave me the idea that I could deduct a number that passes all the tests (product of all the test-factors). This could keep the number low enough, though it was still too large for the int type (number turns negative when too big).

To fix this issue, I had to use a data type which can store bigger integers, so I came across long long int. The max here is 9,223,372,036,854,775,807; which should be more than enough for this task.  