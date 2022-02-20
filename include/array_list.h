#pragma once
#include<ostream>

using namespace std;

namespace ssuds {
	template <class T>
	class ArrayList {
	public:
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ ArrayListIterator                       @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		class ArrayListIterator
		{
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ ArrayListIterator  Attributes           @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		protected:
			ArrayList* mArrayPtr;
			int mCurPosition;
			bool mReverse;

		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ ArrayListIterator OPERATORS             @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
		public:
			ArrayListIterator()
			{
				mArrayPtr = nullptr;
				mCurPosition = -1;
				mReverse = false;
			}

			ArrayListIterator(ArrayList* the_array, int start_index, bool reverse = false)
			{
				mArrayPtr = the_array;
				mCurPosition = start_index;
				mReverse = reverse;
			}

			
			bool operator!= (const ArrayListIterator& other)
			{
				return (mArrayPtr != other.mArrayPtr || mCurPosition != other.mCurPosition || mReverse != other.mReverse);
			}

			bool operator== (const ArrayListIterator& other)
			{
				return (mArrayPtr == other.mArrayPtr && mCurPosition == other.mArrayPtr && mReverse == other.mReverse);
			}

			T& operator* ()
			{
				// return a reference to the current thing we're referring to 
				return (*mArrayPtr)[mCurPosition];
			}

			ArrayListIterator& operator++ ()
			{
				if (mReverse) --mCurPosition;
				else ++mCurPosition;				
				return *this;
			}

			ArrayListIterator operator+(int offset) const
			{
				if (mReverse) return ArrayListIterator(mArrayPtr, mCurPosition - offset);
				else return ArrayListIterator(mArrayPtr, mCurPosition + offset);
			}

		};
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ ATTRIBUTES                              @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	protected:
		unsigned int mSize;
		unsigned int mCapacity;
		static const int msMinCapacity = 5;
		T* mData;

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ CONSTRUCTORS / DESTRUCTORS              @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// Default constructor
		ArrayList() : mSize(0), mData(nullptr), mCapacity(0)
		{

		}
		/// Copy-constructor
		ArrayList(const ArrayList& other) : mSize(other.mSize), mCapacity(other.mCapacity) {
			mData = new T[mCapacity];
			for (int i = 0; i < mSize; i++)
				mData[i] = other[i];

		}
		/// Destructor
		~ArrayList()
		{
			if (mData)
				delete[] mData;
		}
		/// initializer_list constructor
		ArrayList(const initializer_list<T>& ilist)
		{
			mSize = ilist.size();
			mData = new T[mSize];
			mCapacity = mSize;
			int k = 0;
			for (auto s : ilist)
			{
				mData[k] = s;
				k++;
			}
				
		}
		/// move constructor
		ArrayList(ArrayList&& other) noexcept : mSize(move(other.mSize)), mCapacity(move(other.mCapacity)), mData(move(other.mData))
		{
			other.mData = nullptr;
			other.mCapacity = 0;
			other.mSize = 0;
		}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ begin, end, rbegin and rend methods     @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:

		ArrayListIterator begin()
		{
			return ArrayListIterator(this, 0);
		}

		ArrayListIterator end()
		{
			return ArrayListIterator(this, mSize);
		}

		ArrayListIterator rbegin() noexcept
		{
			return ArrayListIterator(this, mSize-1, true);
		}
		ArrayListIterator rend()
		{
			return ArrayListIterator(this, 0, true);
		}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ OPERATOR OVERLOADS                      @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		

	public:

		T& operator[] (const unsigned int index) const
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			return mData[index];
		}

		
		friend ostream& operator<<(ostream& os, const ArrayList& ilist) 
		{
			os << "[";
			for (int i = 0; i < ilist.mSize; i++)
			{
				os << ilist.mData[i];
				if (i < ilist.mSize - 1)
					os << ",";
			}
			os << "]";
			return os;
		}

		ArrayList& operator= (const ArrayList& other) 
		{
			// throw out our existing data (if we have any) 
			if (mData || mSize)
			{
				delete[] mData;
				mData = nullptr;
				mSize = 0;
			}
					
			// Make our own array of at least capacity to hold their elements
			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mData = new T[other.mCapacity];

			// copy elements from other to our array
			for (int i = 0; i < mSize; i++)
				mData[i] = other[i];

			return *this;
		}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ OTHER METHODS (alphabetical)            @		
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		void append(const T val)
		{
			grow();
			mData[mSize] = val;
			mSize++;
		}

		void clear()
		{
			if (mData)
				delete[] mData;
			mData = nullptr;
			mSize = 0;
			mCapacity = 0;
		}

		int find(const T val, int start_index = 0) const
		{
			if (start_index >= mSize || start_index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(start_index));

			for (int i = start_index; i < mSize; i++)
			{
				if (mData[i] == val)
					return i;
			}

			// We didn't find it
			return -1;
		}

		T& get(const int index) const
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			return mData[index];
		}

		void insert(T val, int index)
		{
			if (index > mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			// check to see if we need to increase capacity first
			grow();

			// Move all the elements that come *after* index up one spot
			for (int i = mSize; i > index; i--)
				mData[i] = mData[i - 1];

			// Put our new elements in spot index and increase our size
			mData[index] = val;
			mSize++;
		}

		T remove(int index, bool resize_if_necessary = true)
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			// Get the value we'll return at the end (the element removed)
			T result = mData[index];

			// Move all elements that come after index down one spot
			for (int i = index; i < mSize - 1; i++)
				mData[i] = mData[i + 1];

			// Decrement our size
			mSize--;

			// Shrink, if applicable and requested
			if (resize_if_necessary)
				shrink();

			// Return the result
			return result;
		}

		int remove_all(const T val, bool resize_if_necessary = true)
		{
			int cur_index = 0;
			int num_removed = 0;
			while (cur_index >= 0 && cur_index < mSize)
			{
				// Find the next occurrence of val, starting at the current position
				cur_index = find(val, cur_index);
				if (cur_index >= 0)
				{
					// We found one!
					remove(cur_index, false);
					num_removed++;
				}
			}

			if (resize_if_necessary)
				shrink();

			return num_removed;
		}


		int size() const
		{
			return mSize;
		}

		int capacity() const
		{
			return mCapacity;
		}

	protected:
		void grow()
		{
			if (mSize == mCapacity)
			{
				// Allocate what will become the new array
				T* new_array = nullptr;
				if (mCapacity == 0)
					new_array = new T[msMinCapacity];
				else
					new_array = new T[mCapacity * 2];

				// Copy over data from the old array (if any)
				if (mData != nullptr)
				{
					for (int i = 0; i < mSize; i++)
						new_array[i] = mData[i];

					// Destroy the old array
					delete[] mData;
				}

				// Make the new array *the* array
				mData = new_array;

				// Note that our capacity is now double what it used to be
				if (mCapacity == 0)
					mCapacity = msMinCapacity;
				else
					mCapacity *= 2;
			}
		}

		void shrink()
		{
			if (mSize < mCapacity / 2 && mCapacity >= msMinCapacity * 2)
			{
				// Allocate what will become the new array
				T* new_array = new T[mCapacity / 2];

				// Copy over data from the old array (if any)
				for (int i = 0; i < mSize; i++)
					new_array[i] = mData[i];


				// Destroy the old array
				delete[] mData;

				// Make the new array *the* array
				mData = new_array;

				// Note that our capacity is now double what it used to be
				mCapacity /= 2;
			}
		}

	};	

}