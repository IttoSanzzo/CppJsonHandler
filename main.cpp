#include "./includes/JsonHandler.hpp"

int	main(void) {
	std::cout << "Test Start\n\n";
	
	JsonNode	test;

	test.TryPushData("banana1", (std::string)"skyreach");
	test.TryPushData("conta", 27);
	test.TryPushData("resposta", 27);
	test.TryPushData("senha", (std::string)"vinte e sete");
	JsonNode coisas = JsonNode("coisas");
	coisas.TryPushData("pessego", (std::string)"momotaro");
	coisas.TryPushData("uva", 34);
	test.TryPushData("coisas", coisas);

	// JsonNode temp = JsonNode(coisas);

	
	try {
		std::cout << "\nFINDING\n";
		int result = test.TryGetInt("");
		std::cout << "\nTest Phrases\n\n";
		std::cout << result << std::endl;
	} catch(const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	// jNode1.CreateData("Banana1", (std::string)"Choir Jail");

	// std::cout << jNode1.GetSize() << " " << jNode1.DataNodes->GetPos(0)->GetData()->GetName() << " " << jNode1.DataNodes->GetPos(0)->GetData()->TryGetString() << std::endl;
	// jNode1.CreateData("Banana2", (std::string)"Yahooo");
	// std::cout << jNode1.Data.size() << " " << jNode1.Data[1].GetName() << " " << jNode1.Data[1].TryGetString() << std::endl;

	// jNode1.DeleteData("Bananada1");
	// std::cout << jNode1.Data.size() << " " << jNode1.Data[0].GetName() << " " << jNode1.Data[0].TryGetString() << std::endl;

	// jNode1.DeleteData("Banana1");
	// std::cout << jNode1.Data.size() << " " << jNode1.Data[0].GetName() << " " << jNode1.Data[0].TryGetString() << std::endl;


	std::cout << "\nTest End\n";
	return (0);
}