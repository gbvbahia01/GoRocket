package br.com.mypackage.gorocket;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageButton;
import android.widget.TextView;

import com.google.android.gms.games.Games;
import com.google.android.gms.games.achievement.Achievements;
import com.google.android.gms.games.leaderboard.Leaderboards;
import com.google.example.games.basegameutils.BaseGameActivity;

public class GoogleMoreActivity extends BaseGameActivity implements
		OnClickListener {
	private static int THOUSAND_FEET = 1000;
	private static int FIVE_THOUSAND_FEET = 5000;
	private static int TEN_THOUSAND_FEET = 10000;
	private static int TWENTY_THOUSAND_FEET = 20000;
	private static int THIRTY_THOUSAND_FEET = 30000;
	
	private ImageButton buttonRank;
	private TextView leaderboards;
	private ImageButton buttonTrofeu;
	private TextView achievements;
	private boolean logIn = false;
	
	private int altitude;
	private String email;
	
	@Override
	protected void onCreate(Bundle b) {
		super.onCreate(b);
		setContentView(R.layout.goolgemore);
		altitude = getIntent().getIntExtra("altitude", 0);
		email = getIntent().getStringExtra("email");
		buttonRank = (ImageButton) findViewById(R.id.imageButton2);
		buttonRank.setOnClickListener(this);
		buttonRank.setVisibility(View.GONE);
		leaderboards = (TextView) findViewById(R.id.textView2);
		leaderboards.setVisibility(View.GONE);
		leaderboards.setOnClickListener(this);
		buttonTrofeu = (ImageButton) findViewById(R.id.imageButton1);
		buttonTrofeu.setOnClickListener(this);
		buttonTrofeu.setVisibility(View.GONE);
		achievements = (TextView) findViewById(R.id.textView1);
		achievements.setVisibility(View.GONE);
		achievements.setOnClickListener(this);
		beginUserInitiatedSignIn();
	}

    public Leaderboards getLeaderboards(){
    	return Games.Leaderboards;
    }
    
    public Achievements getAchievements(){
    	return Games.Achievements;
    }
    
	@Override
	public void onSignInFailed() {
		AlertDialog.Builder alert = new AlertDialog.Builder(
				GoogleMoreActivity.this);
		alert.setTitle(R.string.app_name);
		alert.setIcon(R.drawable.ic_no_connection);
		alert.setMessage(R.string.googleMoreErrorLogin);
		alert.setCancelable(false);
		alert.setNeutralButton(R.string.ok,
				new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
						GoogleMoreActivity.this.finish();
					}
				});
		alert.show();
	}

	@Override
	public void onSignInSucceeded() {
		logIn = true;
		buttonRank.setVisibility(View.VISIBLE);
		buttonTrofeu.setVisibility(View.VISIBLE);
		achievements.setVisibility(View.VISIBLE);
		leaderboards.setVisibility(View.VISIBLE);
		int factor = 1;
		if(getString(R.string.my_email).equals(email)){
			factor = 100;
		}
		getLeaderboards().submitScore(getApiClient(), getString(R.string.leaderboard), (int)(altitude / factor));
		if(altitude >= THOUSAND_FEET){
			getAchievements().unlock(getApiClient(), getString(R.string.achievement_1));
		}
		if(altitude >= FIVE_THOUSAND_FEET){
			getAchievements().unlock(getApiClient(), getString(R.string.achievement_2));
		}
		if(altitude >= TEN_THOUSAND_FEET){
			getAchievements().unlock(getApiClient(), getString(R.string.achievement_3));
		}
		if(altitude >= TWENTY_THOUSAND_FEET){
			getAchievements().unlock(getApiClient(), getString(R.string.achievement_4));
		}
		if(altitude >= THIRTY_THOUSAND_FEET){
			getAchievements().unlock(getApiClient(), getString(R.string.achievement_5));
		}
	}

	@Override
	public void onClick(View v) {
		if (logIn) {
			// Rank
			if (v.getId() == R.id.imageButton2 || v.getId() == R.id.textView2) {
				startActivityForResult(
						getLeaderboards().getLeaderboardIntent(getApiClient(), getString(R.string.leaderboard)), 123);//123 can by any number
			}
			// Trophy
			if (v.getId() == R.id.imageButton1 || v.getId() == R.id.textView1) {
				startActivityForResult(getAchievements().getAchievementsIntent(getApiClient()), 124);//124 can by any number
			}
		}
	}

}
