package qlearning.test;


import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

import qlearning.Action;
import qlearning.State;

public class StateTest {
	
	@Test
	public void getLowestScore() {
		State st = new State();
		double score1 = 0.9999999;
		double score2 = 0.0000001;
		double score3 = 0.5;
		double score4 = 0.2;
		
		st.setScore(Action.RIGHT, score1);
		st.setScore(Action.LEFT, score1);
		st.setScore(Action.JUMP, score1);
		st.setScore(Action.RUN, score1);
		assertEquals(Action.RIGHT, st.getLowestScore());
		
		st.setScore(Action.LEFT, score3);
		assertEquals(Action.LEFT, st.getLowestScore());
		
		st.setScore(Action.JUMP, score4);
		assertEquals(Action.JUMP, st.getLowestScore());	
		
		st.setScore(Action.RUN, score2);
		assertEquals(Action.RUN, st.getLowestScore());
		
		st.setScore(Action.LEFT, score3);
		st.setScore(Action.JUMP, score3);
		st.setScore(Action.RUN, score3);
		assertEquals(Action.LEFT, st.getLowestScore());
		
		score1 = 999999999;
		score3 = 0.000000000000000000000000000001;
		score4 = 0;
		
		st.setScore(Action.RIGHT, score1);
		st.setScore(Action.LEFT, score3);
		st.setScore(Action.JUMP, score4);
		
		assertEquals(Action.JUMP, st.getLowestScore());
		


	}
	
	@Test
	public void setScore() {
		State st = new State();
		Exception exception = assertThrows(IllegalArgumentException.class, () -> st.setScore(Action.RUN, -999999999), "Did not throw Exception as expected");
		assertTrue(exception.getMessage().contains("setScore received negative value"));
	}
}
