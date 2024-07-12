[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/NvjFRAHf)

Note: You can use "Makefile" to quickly compile the file, the executable file is named "restaurant".
### Picture 'G' – FAST FOOD RESTAURANT

We create the following objects for this scene:
- Meal
- Side
- Drink

We then wrote a main function that uses these objects to describe the scenario.

Structure of the Classes
`Meal` Class: Represents main dishes, such as burgers or sandwiches. 
It contains the following main components:
- Attributes: Including the dish name, price, and the special sauce chosen by the user.
- Methods: Including a constructor, `chooseSauce` (allows users to choose a sauce for their dish), and `describe` (provides a description of the dish, including name, sauce, and price).

`Side` Class: Represents side dishes, like fries or onion rings. 
Its structure is like the `Meal` class, but it adds a boolean attribute (`spicy`) indicating whether the dish is spicy, and an `askSpicy` method that allows users to choose if they want their side dish to be spicy.

`Drink` Class: Represents optional beverages offered to customers, such as coke, coffee, and water.
It has fewer attributes, mainly including the drink's name and price, along with a `describe` method to output a description of the drink.

Structure of the “main” Function
The main program is responsible for displaying menu options, processing user choices, and calculating and displaying the total price based on the user's selections. The specific steps are as follows:

Displaying Menu Options: Use the `showMealOptions`, `showSideOptions`, and `showDrinkOptions` functions to display the options for main dishes, side dishes, and drinks, respectively.

Processing User Choices:
- The user first chooses from the main dish options, then can select a special sauce for it.
- Next, the user chooses from the side dish options
- Then, deciding if they want it to be spicy and can select a special sauce for it as well.
- Finally, the user selects from the drink options.
Additionally, we have added “None” options to each class option to allow the user to skip that option.

Calculating and Displaying Total Price: Calculate the total price based on the user's selections and display the description of chosen dishes along with the total charge.

An example of a complete interaction is shown below:

Welcome to our Fast Food Restaurant!
Please choose a meal (Enter 0 to skip):
0. None
1. Beef Burger - £5.99
2. Chicken Burger - £5.69
3. Veggie Burger - £5.49
4. Beef Sandwich - £7.49
5. Chicken Sandwich - £6.49

`cin` >> 1

Do you want any special sauce with your Beef Burger? (Enter 'None' or sauce name): None
`cin` >> None

You've chosen no sauce for your Beef Burger.

Please choose a side (Enter 0 to skip):
0. None
1. Fries - £2.49
2. Onion Rings - £2.99
3. Salad - £3.49

`cin` >> 1

Do you want your Fries to be spicy? (1 for Yes, 0 for No): 1
`cin` >> 1

Do you want any special sauce with your Fries? (Enter 'None' or sauce name): Ketchup
`cin` >> Ketchup

You've chosen Ketchup sauce for your Fries.

Please choose a drink (Enter 0 to skip):
0. None
1. Coke - £1.99
2. Sprite - £1.99
3. Dr. Pepper - £1.99
4. Iced Tea - £1.99
5. Milkshake - £2.99
6. Soda - £1.99
7. Water - £0.99
8. Coffee - £2.49

`cin` >> 1

Your order summary:
Beef Burger with no sauce - £5.99
Fries (Spicy) with Ketchup sauce - £2.49
Coke - £1.99
Total price: £10.47
Thank you for your order!
Please feel free to find an available table and you will be notified to pick up your food when it is ready!