#pragma once

class SaveFileError : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Can't write to file\n";
	}
};
