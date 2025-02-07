# Philosophers

![image](https://github.com/user-attachments/assets/c008680f-721b-473f-ac60-b62b52ef19da)

Philosophers is a simulation program written in C that represents a classic dining philosophers problem. The program simulates a group of philosophers sitting at a round table, alternating between eating, thinking, and sleeping. Their goal is to avoid starvation while sharing a bowl of spaghetti and a limited number of forks. 

## Problem Description

Here are the key details of the problem:

- A group of philosophers sits at a round table with a large bowl of spaghetti in the middle.
- The philosophers alternate between three states: eating, thinking, and sleeping.
- While a philosopher is eating, they cannot think or sleep. The same applies to the other states.
- Each philosopher requires two forks to eat. There are as many forks on the table as there are philosophers.
- After finishing their meal, philosophers put their forks back on the table and start sleeping. Upon waking up, they resume thinking.
- The simulation continues until a philosopher dies of starvation.
- It is crucial to ensure that every philosopher has an opportunity to eat and does not starve.
- Philosophers do not communicate or interact directly with each other.
- Philosophers are unaware if another philosopher is on the verge of starvation.
- The objective is to prevent philosophers from dying.
