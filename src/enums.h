typedef enum
{
	INTEGER = 1,
	FLOAT,
	STRING,
	CHAR,
	BOOL
} json_data_type;

typedef enum
{
	False = 0,
	True = 1
} Bool;

typedef enum
{
	EXPECT_KEY,
	EXPECT_COLON,
	EXPECT_CONTENT
} json_state;


typedef enum 
{
	UNKNOWN = 0,
	VALUE,
	ARRAY,
	OBJECT
} json_content_type;





