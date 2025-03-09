#pragma once

class FileError : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Can't read from file\n";
	}
};
