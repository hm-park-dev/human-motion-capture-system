using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace SimpleCircularBuffer
{
    public class SimpleCircularBuffer<T>
	{
        private int capacity;
        private int head, tail, used;
        private T[] buffer;
        
        public SimpleCircularBuffer(int capacity)
        : this(capacity,false)
        {

        }

        public SimpleCircularBuffer(int capacity, bool allowOverflow)
        {
			if (capacity < 0)
			{
				Debug.Log("No capacity");
				return;
			}

            this.capacity = capacity;
            used = 0;
            head = 0;
            tail = 0;
            buffer = new T[capacity];
            AllowOverflow = allowOverflow;
        }

        public bool AllowOverflow
        {
            get;
            set;
        }

        public int Capacity
        {
            get {return capacity;}
        }

        public int Used
        {
            get {return used;}
        }

		public int Head
		{
			get {return head;}
		}

		public int Tail
		{
			get {return tail;}
		}

        public int Push(T[] src)
        {
            return Push(src, 0, src.Length);
        }

        public int Push(T[] src, int srcOffset, int srcLen)
        {
			int actualLen = AllowOverflow ? srcLen : Math.Min(srcLen, capacity - used);
			int srcIndex = srcOffset;

			if (actualLen < srcLen)
			{
				Debug.Log("Buffer overflow");
			}

			for (int i = 0; i < actualLen; i++, tail++, srcIndex++)
			{
				if (tail == capacity)
					tail = 0;
				buffer[tail] = src[srcIndex];
			}

			used = Math.Min(used + actualLen, capacity);
			return actualLen;
        }

		public void Push(T item)
		{
			if (used == capacity)
			{
				Debug.Log("Overflow~");
			}

			buffer[tail] = item;
			if (tail++ == capacity)
				tail = 0;
			used++;
		}

		public T Get(int idx)
		{
			int actualIdx = Math.Min(idx, used);
			actualIdx = (head + actualIdx) % capacity;

			return buffer[actualIdx];
		}

		public T Pop()
		{
			if (used == 0)
			{
				Debug.Log("No data");
				return default(T);
			}

			var item = buffer[head];
			if (head++ == capacity)
				head = 0;

			used--;
			return item;
		}

		public T[] Pop(int size)
		{
			var dst = new T[size];
			Pop(dst);
			return dst;
		}

		public int Pop(T[] dst)
		{
			return Pop(dst, 0, dst.Length);
		}

		public int Pop(T[] dst, int dstOffset, int dstLen)
		{
			int actualLen = Math.Min(dstLen, used);
			int dstIdx = dstOffset;
			for (int i = 0; i < actualLen; i++, head++, dstIdx++)
			{
				if (head == capacity)
					head = 0;

				dst[dstIdx] = buffer[head];
			}

			used -= actualLen;
			return actualLen;
		}

		public IEnumerator<T> GetEnumerator()
		{
			int bufIdx = head;
			for (int i = 0; i < used; i++, bufIdx++)
			{
				if (bufIdx == capacity)
					bufIdx = 0;
			}

			yield return buffer[bufIdx];
		}
    }
}