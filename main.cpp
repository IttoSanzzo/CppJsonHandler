#include "./includes/JsonHandler.hpp"

int	main(void) {
	std::cout << "Test Start\n\n";
	
	JsonNode	test;

	/*
	*/
	test.TryPushData("isthis", true);
	test.TryPushData("banana1", (std::string)"skyreach");
	test.TryPushData("conta", 27);
	test.TryPushData("resposta", 27);
	test.TryPushData("senha", (std::string)"vinte e sete");
	JsonNode coisas = JsonNode("coisas");
	/*
	*/
	coisas.TryPushData("pessegata.coisa", (std::string)"momoCHAN");
	coisas.TryPushData("pessego", (std::string)"momotaro");
	coisas.TryPushData("pessego", (std::string)"momoGYARU");
	coisas.TryPushData("uva", 34);
	test.TryPushData("coisas", coisas);



	// test.DeleteData("coisas.pessegata.coisa");
	try {
		std::cout << "\nFINDING\n";
		// std::string result = test.TryGetString("banana1");
		std::string result = test.TryGetString("coisas.pessegata.coisa");
		std::cout << "\nTest Phrases\n\n";
		std::cout << result << std::endl;
	} catch(const std::exception& ex) {
		std::cout << "\nEEEROOOORR\n\n";
		std::cout << ex.what() << std::endl;
	}
	std::cout << "\nTest End\n";
	return (0);
}