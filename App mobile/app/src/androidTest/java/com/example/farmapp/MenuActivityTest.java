package com.example.farmapp;


import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.action.ViewActions.click;
import static androidx.test.espresso.intent.Intents.intended;
import static androidx.test.espresso.intent.matcher.IntentMatchers.hasComponent;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import androidx.test.espresso.intent.Intents;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.filters.LargeTest;
import androidx.test.internal.runner.junit4.AndroidJUnit4ClassRunner;
import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4ClassRunner.class)
@LargeTest
public class MenuActivityTest {

    @Before
    public void setUp() {
        Intents.init();
    }

    @After
    public void tearDown() {
        Intents.release();
    }


    @Rule
    public  ActivityScenarioRule<MenuActivity> menuActivityRule=
            new ActivityScenarioRule<MenuActivity>(MenuActivity.class);
//tester le bouton retour
    @Test
    public void  testReturnButton(){

        onView(withId(R.id.rtn)).perform(click());
        intended(hasComponent(MainActivity.class.getName()));

    }
// tester le bouton water
    @Test

    public void  testWaterButton(){

        onView(withId(R.id.water)).perform(click());
        intended(hasComponent(WaterActivity.class.getName()));

    }

    @Test

    public void  testFoodrButton(){

        onView(withId(R.id.food)).perform(click());
        intended(hasComponent(FoodActivity.class.getName()));

    }

    @Test

    public void  testLightButton(){

        onView(withId(R.id.light)).perform(click());
        intended(hasComponent(LightActivity.class.getName()));

    }
    @Test

    public void  testCameraButton(){

        onView(withId(R.id.camera)).perform(click());
        intended(hasComponent(CameraActivity.class.getName()));

    }



}