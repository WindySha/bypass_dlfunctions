package com.example.bypass.dlfunctions

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.annotation.Keep
import com.example.bypass.dlfunctions.databinding.ActivityMainBinding

@Keep
class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
    }


    fun clickedBtn(view: View) {
        val result = test_bypass_dlfcn()
        Toast.makeText(this, result, Toast.LENGTH_LONG).show()
    }

    companion object {
        init {
            System.loadLibrary("bypass_dlfunctions_sample")
        }

        @JvmStatic
        @Keep
        external fun test_bypass_dlfcn(): String
    }
}