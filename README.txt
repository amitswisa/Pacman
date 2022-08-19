עמית סויסה - 315507723
הילה עזרא - 207298894

1. כיוון שאנו משתמשים ב filesystem נוצרו בעיות שנפתרו בעזרת הדברים הבאים: 
על מנת להריץ את הפרוייקט שימו לב שהנכם נמצאים בגרסה של C++17 
ובנוסף ב
debug-> debug properties-> C/C++ -> preprocessor -> preprocessor defenition-> Edit (התחילו משמאל לימין)
שיופיע:
WIN32
_DEBUG
_CONSOLE
_HAS_STD_BYTE=0
_SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING


2. בעת הפעלת המשחק במצב Save כל קבצי ה Result + Steps בתיקייה ימחקו ובמקומם ישמרו הקבצים של המשחק האחרון שהשחקן ישחק.