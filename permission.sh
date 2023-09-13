for file in *
do

# check if it is a file
if [ -f $file ]
then

# check if it has all permissions
if [ -r $file ]
then

# print the complete file name with -l option
ls -l $file

# closing second if statement
fi

# closing first if statement
fi

done
