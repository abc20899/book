package cn.junechiu.learnjava.proxy;

/**
 * Created by android on 2017/8/21.
 * 动态代理的应用场景
 * <p>
 * 1. AOP—面向切面编程，程序解耦
 * <p>
 * 简言之当你想要对一些类的内部的一些方法，在执行前和执行后做一些共同的的操作，而在方法中执行个性化操作的时候--用动态代理。
 * 在业务量庞大的时候能够降低代码量，增强可维护性。
 * <p>
 * 2. 想要自定义第三放类库中的某些方法
 * <p>
 * 我引用了一个第三方类库，但他的一些方法不满足我的需求，我想自己重写一下那几个方法，或在方法前后加一些特殊的操作--用动态代理。
 * <p>
 */
public interface RentHouse {
    void rent(); //房屋出租

    void charge(String str); //出租费用收取
}