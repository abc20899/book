### 1.recycle

使用recycle方法可以让系统清理C层所占用的Native内存，这时再调用bitmap的相关方法会引起异常。

```
public void recycle() {
    if (!mRecycled && mNativePtr != 0) {
        if (nativeRecycle(mNativePtr)) {
            // return value indicates whether native pixel object was actually recycled.
            // false indicates that it is still in use at the native level and these
            // objects should not be collected now. They will be collected later when the
            // Bitmap itself is collected.
            mBuffer = null;
            mNinePatchChunk = null;
        }
        mRecycled = true;
    }
}
```
### 2.LRU

LruCache类内部主要是用LinkedHashMap来实现的，提供了put()和get()方法来进行缓存的添加和获取操作；当缓存满了的时候，会用trimToSize()方法将较早的对象移除。

```
//用于存放缓存对象
public final V put(K key, V value) {
    if (key == null || value == null) {
        throw new NullPointerException("key == null || value == null");
    }

    V previous;
    synchronized (this) {
        putCount++;
        size += safeSizeOf(key, value);
        previous = map.put(key, value);
        if (previous != null) {
            size -= safeSizeOf(key, previous);
        }
    }

    if (previous != null) {
        entryRemoved(false, key, previous, value);
    }

    trimToSize(maxSize);
    return previous;
}
```
```
//用于移除缓存对象
public final V remove(K key) {
    if (key == null) {
        throw new NullPointerException("key == null");
    }

    V previous;
    synchronized (this) {
        previous = map.remove(key);
        if (previous != null) {
            size -= safeSizeOf(key, previous);
        }
    }

    if (previous != null) {
        entryRemoved(false, key, previous, null);
    }

    return previous;
}
```
```
//用于将较早的缓存对象移除
public void trimToSize(int maxSize) {
    while (true) {
        K key;
        V value;
        synchronized (this) {
            if (size < 0 || (map.isEmpty() && size != 0)) {
                throw new IllegalStateException(getClass().getName()
                        + ".sizeOf() is reporting inconsistent results!");
            }

            if (size <= maxSize || map.isEmpty()) {
                break;
            }

            Map.Entry<K, V> toEvict = map.entrySet().iterator().next();
            key = toEvict.getKey();
            value = toEvict.getValue();
            map.remove(key);
            size -= safeSizeOf(key, value);
            evictionCount++;
        }

        entryRemoved(true, key, value, null);
    }
}
```
### 3.计算inSampleSize
```
public class BitmapUtils {
    public static int calculateInSampleSize(BitmapFactory.Options options, int reqWidth, int reqHeight) {
        final int height = options.outHeight;
        final int width = options.outWidth;
        int inSampleSize = 1;

        if (height > reqHeight || width > reqWidth) {
            if (width > height) {
                inSampleSize = Math.round((float) height / (float) reqHeight);
            } else {
                inSampleSize = Math.round((float) width / (float) reqWidth);
            } 
        }
        return inSampleSize;
    }
}
```
### 4.缩略图
```
public static Bitmap thumbnail(String path, int maxWidth, int maxHeight, boolean autoRotate) {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        Bitmap bitmap = BitmapFactory.decodeFile(path, options);
        options.inJustDecodeBounds = false;
        
        //计算缩放比
        int sampleSize = calculateInSampleSize(options, maxWidth, maxHeight);
        options.inSampleSize = sampleSize;
        options.inPreferredConfig = Bitmap.Config.RGB_565;
        options.inPurgeable = true;
        options.inInputShareable = true;

        if (bitmap != null && !bitmap.isRecycled()) {
            bitmap.recycle();
        }
        bitmap = BitmapFactory.decodeFile(path, options);
        return bitmap;
}
```
### 5.三级缓存

①网络缓存

②本地缓存

③内存缓存

第一次打开图片先从网络获取，并保存到本地和内存各一份；再次打开图片就从内存或者本地获取，无需再次联网。
