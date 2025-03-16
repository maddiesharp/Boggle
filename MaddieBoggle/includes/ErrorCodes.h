//
// Place Holder Copyright Header
//

#ifndef ERROR_CODE_H
#define ERROR_CODE_H

/// <summary>
/// enum class containing an assortment of error codes 
/// that can be propagated through the system
/// </summary>
enum class ErrorCode
{
	SUCCESS				= 0,
	FILE_NOT_FOUND		= 1,
	UNKNOWN_FILE_ERR	= 2,
	OUT_OF_POOL_SPACE	= 3
};


#endif // ERROR_CODE_H
