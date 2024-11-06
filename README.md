<h1 align="center">C++ Json Handler</h1>

<p align="center"><img width=500px alt="Exemple" src="https://i.imgur.com/66Qzysc.png">
</p>

<p align="center">
<img alt="License" src="https://img.shields.io/badge/license-MIT-blue.svg">
<img alt="C++" src="https://img.shields.io/badge/c++-%2300599C.svg?logo=c%2B%2B&logoColor=white">
</p>

## About It

-   This was done primarily to be used as a parsing method for my other project, a [web server](https://github.com/IttoSanzzo/Webserv) that I handmade practically from scratch.
-   This json parser implements basically all the element forms of a conventional json, such as numbers, strings, booleans and arrays, in a few classes, centered on one named JsonNode.
-   Naturally, since doing it using an easier language, such as C#, wouldn't be any fun, and also doing it using modern C++ and external libraries would make the process rather trivial, I imposed some limitations on myself.
-   For the sake of learning, practicing and, above all, having fun, I decided to follow the C++98 standard and use only the C++ std functions, and nothing else.
-   For that, it ended up costing me entire 2 and a half days to wrap-up a minimally satisfactory version of it.
-   Obliviously, it does not leak memory, and I was not able to break it in none of my... rather simple tests, and common used, till now.
-   But also, because I made fast results a must, while keeping total modularity, it ended up maybe not being the best tool performance or memory wise. BUT, it does attend my demands for the end it was made, flawlessly, and that's what matter the most.
-   And well, I said that, but I'm pretty sure it won't bring any usage problem while not being used to pretty massive ends.

## Compiling and including it in your project

-   First, just clone it in your c++ project directory, and use `make` inside the cloned repository. This will compile the tool into a "jsonReader.a" file.
-   Then, you just has to include it's "JsonHeader.hpp" file wherever you're doing your inclusions, and by compilingo you binary using the given jsonHandler.a file among your sources, it should work just fine, like any other library.

## How to use it

-   With it included, you're now able to use the central "JsonNode" class to your heart's content.
-   This can be populated with any valid external json file, just by using the "TryParseJsonFromFile()", giving it the file's path, or by using the similar "TryParseJsonFromString()" by giving it a complete JsonValid string, and in either case, it will parse the given data, and translate it into usable data.
-   The other way arround can easily be done too, by just using the "ToString()" member function, which will return the complete string from the values in the JsonNode, in the norminal json format, either formated by default, or in a single line giving it "withBreakLines" parameter a false value.

<p align="center"><img alt="JsonHandler Main Example Code" src="https://i.imgur.com/sjnfrNh.png"></p>
<p align="center"><img alt="JsonHandler Main Example Return" src="https://i.imgur.com/66Qzysc.png"></p>

-   Or instead, you can instance it like any other class, with a name, or using the default constructor.
-   From that, you can populate it whatever you like using the TryPushData() member function. It will create a element with the name given, and populate it with the value given alongside it.
-   It sure works with full names, such as element.element.element, and when the elements along the way didn't already exist, they will be created in the process.
-   Wherever a TryPushData() ends in an already existing element, it will then clean it, and change it's value to the given new one.

<p align="center"><img alt="Alter Value Code" src="https://i.imgur.com/yp0LK6J.png"></p>
<p align="center"><img alt="Alter Value Return" src="https://i.imgur.com/13CHdIV.png"></p>

-   Also, to retrieve values from it, you can use any of the "TryGet" member functions, giving it the full name of the element. If it indeed exists, it's value will be retrieved as a copy of the value.

<p align="center"><img alt="Try Get Example Code" src="https://i.imgur.com/kPX22ic.png"></p>
<p align="center"><img alt="Try Get Example Return" src="https://i.imgur.com/pF8RTtN.png"></p>

-   But keep in mind that, wherever you use a member function with "Try" in it's name, it should be used in a try-catch statement, as all the major probably ocurring error during the usage of this library, such as using a "TryGet" for a wrong type of variable, will return a exception with the error details to be dealed with, rather then killing the process.

<p align="center"><img alt="Get Error Code" src="https://i.imgur.com/CBapbd0.png"></p>
<p align="center"><img alt="Get Error Return" src="https://i.imgur.com/WbQxCPp.png"></p>

---

<p align="center">Done with lots of coffee,💜, and C++, by <a href="https://github.com/IttoSanzzo">IttoSanzzo</a>.</p>
