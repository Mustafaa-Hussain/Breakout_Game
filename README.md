# Brick Breaker Game Optimization

This repository contains my optimized version of a **Brick Breaker Game** originally developed by my friend [Ziad-Elshemy](https://github.com/Ziad-Elshemy) after completing an Object-Oriented Programming course.

## 🛠️ Changes Implemented

1. **Efficient Drawing**:
   - Optimized the game loop by ensuring only affected elements (like the paddle, ball, and destroyed bricks) are updated without clearing the entire screen.

2. **Dynamic Brick Removal**:
   - Introduced the `removeBrick` function to clear bricks dynamically once destroyed, improving performance and visuals.

3. **Optimized Score Updates**:
   - Modified the score display logic to refresh only when the score changes.

## 🎮 Gameplay Improvements
- **Before**: The screen would clear and redraw every frame, causing lag and inefficient performance.
- **After**: The game runs smoothly, with only the necessary elements being updated dynamically.

## 🚀 How to Run
1. Make sure you have the required libraries for graphics in C++.
2. Compile the code using BORLANDC.
3. Run the game and enjoy!

## 👏 Acknowledgments
Special thanks to:
- My friend **[Ziad-Elshemy](https://github.com/Ziad-Elshemy)**, for initiating this creative project and collaborating on solving real-world challenges.

---

Feel free to clone, modify, or suggest improvements to this code. Happy coding! 🎉
