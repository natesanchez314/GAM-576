//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "File.h"

namespace Azul
{

	bool File::IsHandleValid(File::Handle fh) noexcept
	{
		DWORD flags;
		if (fh != INVALID_HANDLE_VALUE)
		{
			if (GetHandleInformation(fh, &flags))
				return true;
		}
		return false;
	}

	File::Error File::Open(File::Handle& fh, const char* const fileName, File::Mode mode) noexcept
	{
		if (fileName == nullptr)
			return File::Error::OPEN_FAIL;

		DWORD desiredAccess;
		if (mode == Mode::READ)
			desiredAccess = GENERIC_READ;
		else if (mode == Mode::WRITE)
			desiredAccess = GENERIC_WRITE;
		else
			desiredAccess = GENERIC_ALL;

		HANDLE handle = CreateFile(
			fileName, 
			desiredAccess, 
			0, 
			0, 
			OPEN_ALWAYS, 
			FILE_ATTRIBUTE_NORMAL, 
			nullptr
		);

		if (!IsHandleValid(handle))
			return File::Error::OPEN_FAIL;

		fh = handle;

		return File::Error::SUCCESS;
	}

	File::Error File::Close(File::Handle &fh) noexcept
	{
		if (!IsHandleValid(fh))
			return File::Error::CLOSE_FAIL;

		CloseHandle(fh);

		return File::Error::SUCCESS;
	}

	File::Error File::Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept
	{
		if (!IsHandleValid(fh))
			return File::Error::WRITE_FAIL;

		if (buffer == nullptr)
			return File::Error::WRITE_FAIL;

		if (WriteFile(fh, buffer, inSize, 0, 0))
			return File::Error::SUCCESS;

		return File::Error::WRITE_FAIL;

	}

	File::Error File::Read(File::Handle fh, void* const buffer, const DWORD inSize) noexcept
	{
		if (!IsHandleValid(fh))
			return File::Error::READ_FAIL;

		if (buffer == nullptr)
			return File::Error::READ_FAIL;

		if (ReadFile(fh, buffer, inSize, 0, 0))
			return File::Error::SUCCESS;

		return File::Error::READ_FAIL;
	}

	File::Error File::Seek(File::Handle fh, File::Position location, int offset) noexcept
	{
		DWORD pos;
		if (location == Position::BEGIN)
			pos = FILE_BEGIN;
		else if (location == Position::CURRENT)
			pos = FILE_CURRENT;
		else
			pos = FILE_END;

		if (!IsHandleValid(fh))
			return File::Error::SEEK_FAIL;

		if (SetFilePointer(fh, offset, nullptr, pos) != INVALID_SET_FILE_POINTER)
			return File::Error::SUCCESS;

		return File::Error::SEEK_FAIL;
	}

	File::Error File::Tell(File::Handle fh, DWORD& offset) noexcept
	{
		if (!IsHandleValid(fh))
			return File::Error::TELL_FAIL;

		offset = SetFilePointer(fh, 0, nullptr, FILE_CURRENT);

		return File::Error::SUCCESS;
	}

	File::Error File::Flush(File::Handle fh) noexcept
	{
		if (!IsHandleValid(fh))
			return File::Error::FLUSH_FAIL;

		if (FlushFileBuffers(fh))
			return File::Error::SUCCESS;

		return File::Error::FLUSH_FAIL;
	}

}

// --- End of File ---
