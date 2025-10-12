from datetime import datetime

from zarinpal.models import UnverifiedPayments, UnverifiedTransaction
from zarinpal.enums import Status


def test_unverified_payments_model():
    txn = UnverifiedTransaction(
        authority="A123", amount=1000, callback_url="https://x.com", date=datetime.now()
    )
    resp = UnverifiedPayments(code=Status.SUCCESS, message="ok", authorities=[txn])
    assert resp.success
