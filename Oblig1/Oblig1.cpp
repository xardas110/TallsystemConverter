#include <string>
#include <iostream>
#include <conio.h>

void ThrowIfBaseCheckFailed(const int base)
{
	//More code needs change if higher base is set
	if (base > 36 || base < 2) throw std::exception("Unsupported base");
}

char DecimalBaseToCharBase(int decimal)
{
	if (decimal >= 0 && decimal <= 9)
		return static_cast<char>(decimal + 48);

	if (decimal >= 10 && decimal <= 36)
		return static_cast<char>(decimal + 55);
	
	throw std::exception("Unsupported base");
}

int CharBaseToDecimalBase(const char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - 48;

	if (ch >= 'A' && ch <= 'Z')
		return ch - 55;

	if (ch >= 'a' && ch <= 'z')
		return ch - 87;

	throw std::exception("Unsupported base");
}

std::string InvertString(const std::string _In_& input)
{
	std::string RevertedString{};
	for (int i = static_cast<int>(input.length()) - 1; i > -1; i--)
	{
		RevertedString.push_back(input[i]);
	}
	return RevertedString;
}

void RecursiveDecimalToAnyBase(const int decimal, _Inout_ std::string &result, const int base)
{
	result += DecimalBaseToCharBase(decimal % base);
	const auto quotient = decimal / base;
	if (quotient)
		RecursiveDecimalToAnyBase(quotient, result, base);
}

std::string DecimalToAnyBase(const int val, const int base)
{
	ThrowIfBaseCheckFailed(base);
	
	std::string result{};
	RecursiveDecimalToAnyBase(val, result, base);
	return InvertString(result);
}

int AnyBaseToDecimal(const std::string _In_ &val, const int base)
{
	ThrowIfBaseCheckFailed(base);
	
	int result{};
	for (int i = static_cast<int>(val.length())-1, k=0; i>-1; i--, k++)
		result += CharBaseToDecimalBase(val[i]) * static_cast<int>(pow(base, k));
	return result;
}

int BinaryToDecimal(const std::string &binary)
{
	return AnyBaseToDecimal(binary, 2);
}

std::string BaseConverter(const std::string _Inout_ &val, const int currentBase, const int desiredBase)
{
	return DecimalToAnyBase(AnyBaseToDecimal(val, currentBase), desiredBase);
}

std::string DecimalToBinary(const int decimal)
{
	return DecimalToAnyBase(decimal, 2);
}

std::string BinaryToHex(const std::string _In_ &binary)
{
	return BaseConverter(binary, 2, 16);
}

std::string HexToBinary(const std::string _In_ &hex)
{
	return BaseConverter(hex, 16, 2);
}

int main()
{
	/*
	std::cout << "converting 1000010001001011 to: " << std::endl;
	std::cout << "Base 10: " << AnyBaseToDecimal("1000010001001011", 2) << std::endl;
	std::cout << "Base 8: " << BaseConverter("1000010001001011", 2, 8) << std::endl;
	std::cout << "Base 16: " << BaseConverter("1000010001001011", 2, 16) << std::endl;
	std::cout << "Max base: " << BaseConverter("1000010001001011", 2, 36) << std::endl;
	
	std::cout << std::endl;
	
    std::cout << "Decimal 8 in binary: " << DecimalToBinary(8) << std::endl;
	std::cout << "Binary 1000 to decimal: " << BinaryToDecimal("1000") << std::endl;
	std::cout << "Binary 1100 to hex: " << BinaryToHex("1100") << std::endl;
	std::cout << "Hex C to binary: " << HexToBinary("C") << std::endl;
	*/

	auto option = 0;
	int base = 2;
	do
	{
		std::cout << "Current Base: 2 " << std::endl;
		std::cout << "1. Change base" << std::endl;
		std::cout << "2. Decimal to base " << base << std::endl;
		std::cout << "3. Binary to decimal" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cout << "5. Clear Console " << std::endl;
 
		option = _getch();
		system("CLS");

		switch (option)
		{
			case '1':
			{
				std::cout << "Select new base" << std::endl;
				base = _getch();
				std::cout << "New base is set: " << base << std::endl;
			}
			break;
			case '2':
			{
				std::cout << "Type decimal: " << std::endl;
				std::string decimal;
				std::getline(std::cin, decimal);
				auto binVal = DecimalToAnyBase(atoi(decimal.c_str()), base);
				std::cout << "decimal value in binary: " << binVal << std::endl;
			}
			break;
			case '3':
			{
				std::cout << "Type binary: " << std::endl;
				std::string binary;
				std::getline(std::cin, binary);
				const int val = BinaryToDecimal(binary);
				std::cout << "Binary value in decimal: " << val << std::endl;
			}
			break;
			case '5':
			{
				system("CLS");
			}
			break;
			default:
			break;
		}

		
	} while (option != '4');


	
	return 0;
}
