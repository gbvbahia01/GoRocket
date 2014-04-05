/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package br.com.mypackage.gorocket;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.games.Games;

public class GoRocket extends BaseGameActivity  implements GameHelper.GameHelperListener{
	private static GoRocket reference;
	private AdView adView;
	private InterstitialAd interstitial;
	private String accountCharged = null;
	private boolean tablet = false;
	private boolean debug = false;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		reference = this;
	    carregarEmail();
	    if(!getString(R.string.my_email).equals(accountCharged)){
	    	if(isTablet(this)){
	    		Log.i("ADS", "BANNER");
	    		LayoutParams adParams = new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT);
	    		LinearLayout layout = new LinearLayout(this);
	            layout.setOrientation(LinearLayout.VERTICAL);
	    		tablet = true;
	    		adView = new AdView(this);
	    	    adView.setAdSize(AdSize.BANNER);
	    	    adView.setAdUnitId(getString(R.string.my_admob_id));
	    		AdRequest adRequest = new AdRequest.Builder().build();
	    		adView.loadAd(adRequest);
	    		layout.addView(adView);
	    		addContentView(layout, adParams);
	    	}else {
	    		Log.i("ADS", "InterstitialAd");
	    		tablet = false;
	    		interstitial = new InterstitialAd(this);
	    	    interstitial.setAdUnitId(getString(R.string.my_admob_id));
	    	}
	    }else{
	    	Log.i("EMAIL", "MY_EMAIL HI GBVBAHIA!!!!!!");
	    }
	}

    @Override
	protected void onPostCreate(Bundle savedInstanceState) {
		super.onPostCreate(savedInstanceState);
		 beginUserInitiatedSignIn();
		 carregarEmail();
	}

	public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// GoRocket should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
    
    /** Called when the Load Interstitial button is clicked. */
  	private void loadInterstitial() {
  		carregarEmail();
  		if (!getString(R.string.my_email).equals(accountCharged) && !tablet && interstitial != null) {
  			runOnUiThread(new Runnable() {
  				@Override
  				public void run() {
  					AdRequest adRequest = new AdRequest.Builder().build();
  					interstitial.loadAd(adRequest);
  				}
  			});
  		}else {
  			Log.i("INTERSTITIAL","LOAD: loadInterstitial");
  		}
  	}
  	
  	private void displayInterstitial() {
  		carregarEmail();
  			runOnUiThread(new Runnable() {
  			@Override
  			public void run() {
  				if (!getString(R.string.my_email).equals(accountCharged) && !tablet && interstitial != null && interstitial.isLoaded()) {
  					interstitial.show();
  				}else {
  					Log.i("INTERSTITIAL","SHOW: displayInterstitial");
  				}
  			}
  		});
  	}
  	
  	private void carregarEmail() {
  		if (accountCharged == null) {
  			AccountManager am = AccountManager.get(this);
  			Account[] accounts = am.getAccountsByType("com.google");
  			if (accounts.length > 0) {
  				accountCharged = accounts[0].name;
  			}else {
  				accountCharged = "";
  			}
  		}
  	}
  	
	/**
	 *  Retorna se a tela e large ou xlarge
	 * @param context
	 * @return
	 */
	public static boolean isTablet(Context context) {
	    return (context.getResources().getConfiguration().screenLayout
	            & Configuration.SCREENLAYOUT_SIZE_MASK)
	            >= Configuration.SCREENLAYOUT_SIZE_LARGE;
	}
 	
    @Override
    public void onResume() {
      super.onResume();
      if (adView != null) {
        adView.resume();
      }
    }

    @Override
    public void onPause() {
      if (adView != null) {
        adView.pause();
      }
      super.onPause();
    }
    

    /** Called before the activity is destroyed. */
    @Override
    public void onDestroy() {
      // Destroy the AdView.
      if (adView != null) {
        adView.destroy();
      }
      super.onDestroy();
    }
    
    @Override
    public void onSignInFailed() {
    	Log.w("GOROCKET_SCORE_SHARE", "Fail to SignIn Failed Google Play Games");
    	//Toast.makeText(this, "Fail to SignIn on Google Play Games", Toast.LENGTH_LONG).show();
    }

    @Override
    public void onSignInSucceeded() {
    	if(debug){
    		Toast.makeText(this, "Success to SignIn Google Play Games", Toast.LENGTH_LONG).show();
    		Log.w("GOROCKET_SCORE_SHARE", "Success to SignIn Google Play Games");
    	}
    	Log.w("GOROCKET_SCORE_SHARE", "Success to SignIn Google Play Games");
    }
    
  //static SHARE API
  	public static String share(final int altitude) {
  		if (reference == null) {
  			return "Lasco";
  		}
		reference.runOnUiThread(new Runnable() {
			public void run() {
		  		final Intent intent = new Intent(Intent.ACTION_SEND);
		  		intent.setType("text/plain");
		  		intent.putExtra(Intent.EXTRA_TEXT,
		  				"My altitude in GO ROCKET is: " + altitude + " https://play.google.com/store/apps/details?id=br.com.mypackage.gorocket");
		  		reference.startActivity(Intent.createChooser(intent, "Share with:"));
			}});
  		return "UFA";
  	}
  	
  	//COMERCIAL
	public static void showInterstitial(final int fileFase) {
		if (reference == null) {
			return ;
		}
		if(!reference.tablet){
			if(fileFase == 3){
				reference.displayInterstitial();
			}else if(fileFase == 1){
				reference.loadInterstitial();
			}
		}
		return ;
	}
  	
  	//PLAY GOOGLE
	private static int THOUSAND_FEET = 1000;
	private static int FIVE_THOUSAND_FEET = 5000;
	private static int TEN_THOUSAND_FEET = 10000;
	private static int TWENTY_THOUSAND_FEET = 20000;
	private static int THIRTY_THOUSAND_FEET = 30000;
	
	public static void gameServicesPostRecord(int altitude) {
		Log.i("PLAY GOOGLE", "Public Record");
		if (reference != null && reference.mHelper.isSignedIn()) {
			int factor = 1;
			if(reference.getString(R.string.my_email).equals(reference.accountCharged)){
				factor = 10;
			}
			Games.Leaderboards.submitScore(reference.getApiClient(), reference.getString(R.string.leaderboard), (int)(altitude / factor));
			if(altitude >= THOUSAND_FEET){
				Games.Achievements.unlock(reference.getApiClient(), reference.getString(R.string.achievement_1));
			}
			if(altitude >= FIVE_THOUSAND_FEET){
				Games.Achievements.unlock(reference.getApiClient(), reference.getString(R.string.achievement_2));
			}
			if(altitude >= TEN_THOUSAND_FEET){
				Games.Achievements.unlock(reference.getApiClient(), reference.getString(R.string.achievement_3));
			}
			if(altitude >= TWENTY_THOUSAND_FEET){
				Games.Achievements.unlock(reference.getApiClient(), reference.getString(R.string.achievement_4));
			}
			if(altitude >= THIRTY_THOUSAND_FEET){
				Games.Achievements.unlock(reference.getApiClient(), reference.getString(R.string.achievement_5));
			}
		}
	}
	
	public static void gameServicesShowRecord() {
		Log.i("PLAY GOOGLE", "Show Record");
		if (reference != null && reference.mHelper.isSignedIn()) {
			reference.startActivityForResult(Games.Leaderboards.getLeaderboardIntent(reference.getApiClient(),
									reference.getString(R.string.leaderboard)), 123);// 123 can by any number
		}
	}
	
	public static void gameServicesShowMedals() {
		Log.i("PLAY GOOGLE", "Medals");
		if (reference != null && reference.mHelper.isSignedIn()) {
			reference.startActivityForResult(Games.Achievements.getAchievementsIntent(reference.getApiClient()), 123);// 123 can by any number
		}
	}
}
