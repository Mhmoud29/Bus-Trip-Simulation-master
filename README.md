# Bus Trip Simulation
Imagine a bustling city with passengers eager to navigate its intricate web of routes. This bus trip simulation takes the helm, meticulously assigning riders to their journeys. Gone are the days of haphazard boarding and inefficient bus schedules. Our program empowers the transit system to optimize passenger flow, considering diverse factors like arrival times, and desired destinations. By leveraging intelligent algorithms and robust data structures, this simulation orchestrates a symphony of bus movements, ensuring riders reach their stops as smoothly and efficiently as possible. Every detail is accounted for, from passenger priority to dynamic rerouting, optimizing the entire transit ecosystem and providing valuable insights for further improvement.

## Types of Passengers:
1- Special Passengers:
<ul>
  <li>These are high-priority Pasengers that need to be assigned first.</li>
  <li>They have sub priorites in them:
  <ul>
    <li>Aged: have the highest priority</li>
    <li>People of Determination (POD) : have the second highest priority</li>
    <li>Pregnent Women (PREG): have the third highest priority</li>
  </ul>
  </li>
</ul>
2- Normal Passengers:
<ul>
  <li>These are Normal Passengers that do not have any specific requirements.</li>
</ul>
2- Wheel Chair Passengers:
<ul>
  <li>These are Passengers that do not have the ability to move by themselves but on a Wheel chair and they have their own bus</li>
</ul>

## Types of Busses:
1- Mixed Bus:
<ul>
  <li>This Bus only allow the Normal Passengers and the Special Passengers to be assigned to it</li>
  <li>Passengers are assigned first according their priorities:

  1-Aged
  
  2-POD

  3-Preg

  4-Normal
  </li>
</ul>

2- Wheel Chair Bus:
<ul>
  <li>Only allow the wheel chair passengers to be assigned to it</li>
</ul>
The program takes into account the type of Busses available and assigns the appropriate Passengers based on the passenger type and Bus availability.


## Data Structures Used:
In this project, various data structures were utilized to optimize the Bus Trip simulation. These data structures were implemented as templates and coded from scratch. The following data structures were employed:
<ul>
  <li>Queue: Implemented as a FIFO (first in, first out) data structure, the queue was used for the event list. This allows for efficient execution of events in their order of insertion. and also when Assigning the Wheel chair passengers to their bus</li>
  <li>Priority Queue: Used to prioritize the Special passengers in their subcategories and also prioritize the special passengers as a whole over the Normal passenger when assigning them to the mixed bus</li>
  <li>Linked List: A linked list data structure was employed for various purposes throughout the project. It offers flexibility in managing and manipulating data, enabling efficient insertion, deletion, and traversal operations. Example:
  <ul>
    <li>Used for the implementation of the finished passenger List</li>
  </ul>
  </li>

</ul>

For more detailed information on the usage of each data structure for specific objects and the rationale behind their selection, please refer to the documentation available in the [GitHub repository](https://github.com/yusufafify/Bus-Trip-Simulation/blob/master/Data%20Structures%20Documentation.pdf). The documentation provides insights into the design choices and the advantages of utilizing particular data structures for different components of the project.

## Previews:
The user enters the File name and choose the Type of the simulation he wants:
<ul>
  <li>IF Silent Mode
  
![Screenshot 2024-01-25 154356](https://github.com/yusufafify/Bus-Trip-Simulation/assets/115397064/805dbcfc-7df2-4361-9a77-dbfa0d881484)
  </li>

  <li>IF interactive Mode
  
![Screenshot 2024-01-25 154226](https://github.com/yusufafify/Bus-Trip-Simulation/assets/115397064/9ee83583-72f0-4390-89b0-db20e84508d2)
  </li>
</ul>
Output file Generated:

![Screenshot 2024-01-25 154138](https://github.com/yusufafify/Bus-Trip-Simulation/assets/115397064/814e562f-6052-43ba-aaea-dba9f6689b13)
