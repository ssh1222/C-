class Solution {
public:
	void replaceSpace(char *str, int length)
	{
		if (str == NULL || length == 0)
			return;
		int blankNum = 0;
		int originLength = 0;
		int i = 0;
		while (str[i] != '\0'){
			++originLength;
			if (str[i] == ' ')
				++blankNum;
			++i;
		}
		int newLength = originLength + blankNum * 2;
		if (newLength > length)
			return;
		int newPlace = newLength;
		int originPlace = originLength;
		while (originPlace >= 0 && newPlace > originPlace){
			if (str[originPlace] != ' ')
				str[newPlace--] = str[originPlace];
			else{
				str[newPlace--] = '0';
				str[newPlace--] = '2';
				str[newPlace--] = '%';
			}
			--originPlace;
		}
	}
};